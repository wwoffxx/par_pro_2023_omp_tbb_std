  // Copyright 2023 Nikolaev Alexander
#include <random>
#include <algorithm>
#include "../../../modules/task_1/nikolaev_a_mult_sparse_matr/sparse_matrix.h"

void printMatrix(const std::vector<std::vector<Complex>>& Pmatrix) {
    const size_t sizeMatrix = Pmatrix.size();
    for (int i = 0; i < sizeMatrix; i++) {
        for (int j = 0; j < sizeMatrix; j++) {
            std::cout << Pmatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

CCSMatrix GetRandomMatrix(int N, int nonZero) {
    CCSMatrix mtx;
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<> disValue(0, 10);
    std::uniform_int_distribution<> disIndex(0, N - 1);
    std::vector<std::vector<Complex>> matrix(N, std::vector<Complex>(N));
    mtx.sizeMatrix = N;
    int row = 0;
    int col = 0;
    for (int i = 0; i < nonZero; i++) {
        row = disIndex(gen);
        col = disIndex(gen);
        while (matrix[row][col] != Complex(0, 0)) {
            row = disIndex(gen);
            col = disIndex(gen);
        }
        matrix[row][col] = Complex(disValue(gen), disValue(gen));
    }

    int ind = 0;
    mtx.colIndex.push_back(0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
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


void TransposeMatrix(CCSMatrix* A) {
    CCSMatrix AT;

    AT.sizeMatrix = A->sizeMatrix;
    AT.countNZ = A->countNZ;
    AT.colIndex.resize(A->colIndex.size());
    AT.rowIndex.resize(A->rowIndex.size());
    AT.value.resize(A->value.size());

    for (int i = 0; i < A->countNZ; i++) {
        AT.colIndex[A->rowIndex[i] + 1]++;
    }

    int tmp = 0;
    int S = 0;
    for (int i = 1; i <= A->sizeMatrix; i++) {
        tmp = AT.colIndex[i];
        AT.colIndex[i] = S;
        S = S + tmp;
    }
    int j1 = 0;
    int j2 = 0;
    int Col = 0;
    Complex V = {0, 0};
    int RIndex = 0; int IIndex = 0;
    for (int i = 0; i < A->sizeMatrix; i++) {
        j1 = A->colIndex[i]; j2 = A->colIndex[i + 1];
        Col = i;
        for (int j = j1; j < j2; j++) {
            V = A->value[j];
            RIndex = A->rowIndex[j];
            IIndex = AT.colIndex[RIndex + 1];
            AT.value[IIndex] = V;
            AT.rowIndex[IIndex] = Col;
            AT.colIndex[RIndex + 1]++;
        }
    }
    A->value = AT.value;
    A->colIndex = AT.colIndex;
    A->rowIndex = AT.rowIndex;
}

CCSMatrix MatrixtoCCSMatrix(const std::vector<std::vector<Complex>> &matrix) {
    const int SizeMatrix = matrix.size();
    CCSMatrix A;
    A.sizeMatrix = SizeMatrix;
    int ind = 0;
    A.colIndex.push_back(0);

    for (int i = 0; i < SizeMatrix; ++i) {
        for (int j = 0; j < SizeMatrix; ++j) {
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

CCSMatrix Multiplicate(const CCSMatrix& A, const CCSMatrix& B) {
    CCSMatrix C;
    C.sizeMatrix = A.sizeMatrix;
    C.colIndex.push_back(0);
    int NonZero = 0;
    for (int i = 0; i < A.sizeMatrix; i++) {
        for (int j = 0; j < A.sizeMatrix; j++) {
            Complex sum = 0;
            int ks = A.colIndex[i];
            int ls = B.colIndex[j];
            int kf = A.colIndex[i + 1] - 1;
            int lf = B.colIndex[j + 1] - 1;
            while ((ks <= kf) && (ls <= lf)) {
                if (A.rowIndex[ks] < B.rowIndex[ls]) {
                    ks++;
                } else if (A.rowIndex[ks] > B.rowIndex[ls]) {
                    ls++;
                } else {
                    sum += A.value[ks] * B.value[ls];
                    ks++;
                    ls++;
                }
            }
            if (sum.real() != 0) {
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
