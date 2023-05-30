// Copyright 2023 Mokrousov Artem
#include "../../../modules/task_3/mokrousov_a_crs_mult_matrix_tbb/crs_mult_matrix_tbb.h"

CRSMatrix::CRSMatrix(int nC, int nR, const std::vector<double>& v,
                     const std::vector<int>& c, const std::vector<int>& p)
    : nColumns(nC), nRows(nR), values(v), columns(c), pointers(p) {}

CRSMatrix::CRSMatrix(std::vector<std::vector<double>> mtx) {
    nColumns = mtx[0].size();
    nRows = mtx.size();

    int elemCounter = 0;
    pointers.push_back(elemCounter);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            if (mtx[i][j] != 0) {
                elemCounter = elemCounter + 1;
                values.push_back(mtx[i][j]);
                columns.push_back(j);
            }
        }
        pointers.push_back(elemCounter);
    }
}

CRSMatrix::CRSMatrix(int nC, int nR) {
    nColumns = nC;
    nRows = nR;
}

CRSMatrix CRSMatrix::T() {
    std::vector<std::vector<int>> intVectors(nColumns);
    std::vector<std::vector<double>> valueVectors(nColumns);
    CRSMatrix mtxT;

    mtxT.nRows = nColumns;
    mtxT.nColumns = nRows;
    int elemCounter = 0;
    for (int i = 0; i < nRows; i++) {
        for (int k = pointers[i]; k < pointers[i + 1]; k++) {
            int colInd = columns[k];
            intVectors[colInd].push_back(i);
            valueVectors[colInd].push_back(values[k]);
        }
    }
    mtxT.pointers.push_back(elemCounter);
    for (int i = 0; i < nColumns; i++) {
        for (size_t k = 0; k < intVectors[i].size(); k++) {
            mtxT.columns.push_back(intVectors[i][k]);
            mtxT.values.push_back(valueVectors[i][k]);
        }
        elemCounter = elemCounter + intVectors[i].size();
        mtxT.pointers.push_back(elemCounter);
    }
    return mtxT;
}

CRSMatrix CRSMatrix::dot(CRSMatrix mtx) {
    std::vector<int> resCol;
    std::vector<double> resValue;
    std::vector<int> resPointer;
    int nZRow = 0;
    int resRows = nRows;
    int resCols = mtx.nColumns;
    if (nColumns != mtx.nColumns)
        throw std::runtime_error("Error! Number of rows is incorrect :(\n");
    nZRow = 0;
    resRows = nRows;
    resCols = mtx.nColumns;
    resPointer.push_back(nZRow);
    for (int i = 0; i < nRows; i++) {
        // i - number of the processed row of the left matrix
        nZRow = 0;
        for (int j = 0; j < mtx.nRows; j++) {
            // j - number of the processed column of the right matrix
            double summ = 0;
            int ls = mtx.pointers[j];
            int lf = mtx.pointers[j + 1] - 1;
            int ks = pointers[i];
            int kf = pointers[i + 1] - 1;
            while ((lf >= ls) && (kf >= ks)) {
                if (columns[ks] > mtx.columns[ls]) {
                    ls = ls + 1;
                } else {
                    if (columns[ks] < mtx.columns[ls]) {
                        ks = ks + 1;
                    } else {
                        summ = summ + values[ks] * mtx.values[ls];
                        ls = ls + 1;
                        ks = ks + 1;
                    }
                }
            }

            if (summ != 0) {
                nZRow = nZRow + 1;
                resValue.push_back(summ);
                resCol.push_back(j);
            }
        }
        resPointer.push_back(nZRow + resPointer[i]);
    }

    CRSMatrix res(resCols, resRows, resValue, resCol, resPointer);
    return res;
}

CRSMatrix CRSMatrix::tbbDot(CRSMatrix mtx) {
    std::vector<int> resCol;
    std::vector<double> resValue;
    std::vector<int> resPointer;
    int resRows = nRows;
    int resCols = mtx.nColumns;
    std::vector<std::vector<int>> locCol(nRows);
    std::vector<std::vector<double>> locVal(nRows);
    if (nColumns != mtx.nColumns)
        throw std::runtime_error("Error! Number of rows is incorrect :(\n");
    resRows = nRows;
    resCols = mtx.nColumns;
    int grainSize = 10;
    tbb::parallel_for(
        tbb::blocked_range<int>(0, nRows, grainSize),
        [&](tbb::blocked_range<int> r) {
            for (int i = r.begin(); i != r.end(); i++) {
                for (int j = 0; j < mtx.nRows; j++) {
                    double summ = 0;
                    int sCur = mtx.pointers[j];
                    int sEnd = mtx.pointers[j + 1] - 1;
                    int fCur = pointers[i];
                    int fEnd = pointers[i + 1] - 1;
                    while ((sEnd >= sCur) && (fEnd >= fCur)) {
                        if (columns[fCur] > mtx.columns[sCur]) {
                            sCur = sCur + 1;
                        } else {
                            if (columns[fCur] < mtx.columns[sCur]) {
                                fCur = fCur + 1;
                            } else {
                                summ = summ + values[fCur] * mtx.values[sCur];
                                sCur = sCur + 1;
                                fCur = fCur + 1;
                            }
                        }
                    }
                    if (summ != 0) {
                        locVal[i].push_back(summ);
                        locCol[i].push_back(j);
                    }
                }
            }
        });
    int elemCounter = 0;
    resPointer.push_back(elemCounter);
    for (int i = 0; i < nRows; i++) {
        resCol.insert(resCol.end(), locCol[i].begin(), locCol[i].end());
        resValue.insert(resValue.end(), locVal[i].begin(), locVal[i].end());
        elemCounter = elemCounter + locCol[i].size();
        resPointer.push_back(elemCounter);
    }
    CRSMatrix res(resCols, resRows, resValue, resCol, resPointer);
    return res;
}

void CRSMatrix::arraysPrint() {
    std::cout << "values:\n";
    for (size_t i = 0; i < values.size(); i++) {
        std::cout << values[i] << " ";
    }
    std::cout << "\ncolumns:\n";
    for (size_t i = 0; i < columns.size(); i++) {
        std::cout << columns[i] << " ";
    }
    std::cout << "\npointer:\n";
    for (size_t i = 0; i < pointers.size(); i++) {
        std::cout << pointers[i] << " ";
    }
    std::cout << "\n";
}

std::vector<std::vector<double>> zerpMatrix(int cols, int rows) {
    std::vector<std::vector<double>> res(rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) res[i].push_back(0);
    }
    return res;
}

bool CRSMatrix::operator==(const CRSMatrix& mtx) const {
    bool check = false;
    if ((nColumns == mtx.nColumns) && (nRows == mtx.nRows) &&
        (values == mtx.values) && (columns == mtx.columns) &&
        (pointers == mtx.pointers))
        check = true;
    return check;
}

std::vector<std::vector<double>> genMatrix(int cols, int rows, double density) {
    if (density > 1 || density < 0) {
        throw std::runtime_error("Error: Percentage is incorrect :(\n");
    }
    std::vector<std::vector<double>> res = zerpMatrix(cols, rows);
    std::mt19937 gen;
    std::uniform_real_distribution<double> prob{0.0, 1.0};
    std::uniform_real_distribution<double> value{0.0, 13.0};
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (prob(gen) <= density) {
                res[i][j] = value(gen);
            }
        }
    }
    return res;
}

std::vector<std::vector<double>> mulMatrix(std::vector<std::vector<double>> A,
                                           std::vector<std::vector<double>> B) {
    int rows = A.size();
    int cols = B[0].size();
    std::vector<std::vector<double>> C = zerpMatrix(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = 0;
            for (size_t k = 0; k < A[0].size(); ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}
