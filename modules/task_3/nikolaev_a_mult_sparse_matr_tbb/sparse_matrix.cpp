  // Copyright 2023 Nikolaev Alexander
#include <random>
#include <algorithm>
#include "../../../modules/task_3/nikolaev_a_mult_sparse_matr_tbb/sparse_matrix.h"

void printMatrix(const std::vector<std::vector<Complex>>& Pmatrix) {
    const size_t sizeRow = Pmatrix.size();
    const size_t sizeCol = Pmatrix[0].size();
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            std::cout << Pmatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

CCSMatrix GetRandomMatrix(int SizeRow, int SizeCol, int nonZero) {
    CCSMatrix mtx;
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<> disValue(1, 10);
    std::uniform_int_distribution<> disRowIndex(0, SizeRow - 1);
    std::uniform_int_distribution<> disColIndex(0, SizeCol - 1);
    std::vector<std::vector<Complex>> matrix(SizeRow,
                std::vector<Complex>(SizeCol));
    mtx.sizeRow = SizeRow;
    mtx.sizeCol = SizeCol;
    int row = 0;
    int col = 0;
    for (int i = 0; i < nonZero; i++) {
        row = disRowIndex(gen);
        col = disColIndex(gen);
        while (matrix[row][col] != Complex(0, 0)) {
            row = disRowIndex(gen);
            col = disColIndex(gen);
        }
        matrix[row][col] = Complex(disValue(gen), 0);
    }

    int ind = 0;
    mtx.colIndex.push_back(0);
    for (int i = 0; i < SizeCol; i++) {
        for (int j = 0; j < SizeRow; j++) {
            if (matrix[j][i] == Complex(0, 0)) {
                continue;
            }
            mtx.value.push_back(matrix[j][i]);
            mtx.rowIndex.push_back(j);
            ind++;
        }
        mtx.colIndex.push_back(ind);
    }
    mtx.countNZ = mtx.rowIndex.size();
    return mtx;
}

CCSMatrix TransposeMatrix(const CCSMatrix& A) {
    CCSMatrix AT;

    AT.sizeCol = A.sizeRow;
    AT.sizeRow = A.sizeCol;
    AT.countNZ = A.countNZ;

    std::vector<std::vector<int>> rows(A.sizeRow);
    std::vector<std::vector<Complex>> values(A.sizeRow);

    for (int i = 0; i < A.sizeCol; ++i) {
        for (int j = A.colIndex[i]; j < A.colIndex[i + 1]; ++j) {
            rows[A.rowIndex[j]].push_back(i);
            values[A.rowIndex[j]].push_back(A.value[j]);
        }
    }

    AT.colIndex.resize(AT.sizeCol + 1);
    AT.colIndex[0] = 0;

    for (int i = 0; i < AT.sizeCol; ++i) {
        AT.colIndex[i + 1] = AT.colIndex[i] + values[i].size();
        int n = values[i].size();
        for (int j = 0; j < n; ++j) {
            AT.value.push_back(values[i][j]);
            AT.rowIndex.push_back(rows[i][j]);
        }
    }
    return AT;
}

CCSMatrix GetMultiplicateSequential(const CCSMatrix& A, const CCSMatrix& B) {
    CCSMatrix C;

    C.sizeRow = A.sizeCol;
    C.sizeCol = B.sizeCol;
    C.colIndex.push_back(0);

    int NonZero = 0;

    for (int i = 0; i < A.sizeCol; ++i) {
        std::vector<int> tmp(A.sizeRow, -1);
        for (int t = A.colIndex[i]; t < A.colIndex[i + 1]; ++t) {
            int row = A.rowIndex[t];
            tmp[row] = t;
        }
        for (int j = 0; j < B.sizeCol; ++j) {
            Complex sum = 0;
            for (int k = B.colIndex[j]; k < B.colIndex[j + 1]; ++k) {
                int row = B.rowIndex[k];
                int index = tmp[row];
                if (index > -1) {
                    sum += A.value[index] * B.value[k];
                }
            }
            if (sum.real() != 0 || sum.imag() != 0) {
                C.rowIndex.push_back(j);
                C.value.push_back(sum);
                NonZero++;
            }
        }
        C.colIndex.push_back(NonZero);
    }
    C.countNZ = NonZero;

    return C;
}

CCSMatrix GetMultiplicateParallel(const CCSMatrix& A, const CCSMatrix& B) {
    CCSMatrix C;

    C.sizeRow = A.sizeCol;
    C.sizeCol = B.sizeCol;
    C.colIndex.push_back(0);

    std::vector<std::vector<Complex>> values(A.sizeRow);
    std::vector<std::vector<int>> indexesRow(A.sizeRow);
    std::vector<std::vector<int>> indexesCol(C.sizeCol + 1);

    tbb::parallel_for(tbb::blocked_range<int>(0, A.sizeCol),
        [&](tbb::blocked_range<int>& r) {
        for (int i = r.begin(); i < r.end(); ++i) {
            std::vector<int> tmp(A.sizeRow, -1);
            int NonZero = 0;
            std::vector<Complex> threadValues;
            std::vector<int> threadIndexesRow;
            std::vector<int> threadIndexesCol;
            for (int t = A.colIndex[i]; t < A.colIndex[i + 1]; ++t) {
                int row = A.rowIndex[t];
                tmp[row] = t;
            }
            for (int j = 0; j < B.sizeCol; ++j) {
                Complex sum = 0;
                for (int k = B.colIndex[j]; k < B.colIndex[j + 1]; ++k) {
                    int row = B.rowIndex[k];
                    int index = tmp[row];
                    if (index > -1) {
                        sum += A.value[index] * B.value[k];
                    }
                }
                if (sum.real() != 0 || sum.imag() != 0) {
                    NonZero++;
                    threadValues.push_back(sum);
                    threadIndexesRow.push_back(j);
                }
            }
            values[i] = threadValues;
            indexesCol[i].push_back(NonZero);
            indexesRow[i] = threadIndexesRow;
        }
    });

    for (int i = 0; i < A.sizeRow; i++) {
        C.value.insert(C.value.end(), values[i].begin(), values[i].end());
        C.rowIndex.insert(C.rowIndex.end(),
            indexesRow[i].begin(),
            indexesRow[i].end());
    }

    for (int i = 0; i < C.sizeCol; i++) {
        C.colIndex.insert(C.colIndex.end(),
            indexesCol[i].begin(),
            indexesCol[i].end());
    }

    C.countNZ = C.value.size();

    return C;
}

CCSMatrix MatrixtoCCSMatrix(const std::vector<std::vector<Complex>>& matrix) {
    const int sizeRow = matrix.size();
    const int sizeCol = matrix[0].size();
    CCSMatrix A;
    A.sizeRow = sizeRow;
    A.sizeCol = sizeCol;
    int ind = 0;
    A.colIndex.push_back(0);

    for (int i = 0; i < sizeCol; ++i) {
        for (int j = 0; j < sizeRow; ++j) {
            if (matrix[j][i] == Complex(0, 0)) {
                continue;
            }
            A.value.push_back(matrix[j][i]);
            A.rowIndex.push_back(j);
            ind++;
        }
        A.colIndex.push_back(ind);
    }
    A.countNZ = ind;
    return A;
}
