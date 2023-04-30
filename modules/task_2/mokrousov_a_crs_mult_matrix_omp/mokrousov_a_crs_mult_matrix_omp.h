// Copyright 2023 Mokrousov Artem
#ifndef MODULES_TASK_2_MOKROUSOV_A_CRS_MULT_MATRIX_OMP_MOKROUSOV_A_CRS_MULT_MATRIX_OMP_H_
#define MODULES_TASK_2_MOKROUSOV_A_CRS_MULT_MATRIX_OMP_MOKROUSOV_A_CRS_MULT_MATRIX_OMP_H_

#include <vector>

struct Matrix {
    std::vector<int> values;
    std::vector<int> colums;
    std::vector<int> pointer;

    Matrix() {}

    Matrix(const std::vector<int>& _values, const std::vector<int>& _colums,
           const std::vector<int>& _pointer)
        : values(_values), colums(_colums), pointer(_pointer) {}

    void merge(Matrix A) {
        values.insert(values.begin(), A.values.begin(), A.values.end());
        colums.insert(colums.begin(), A.colums.begin(), A.colums.end());

        for (auto i : A.pointer) pointer.push_back(i + pointer.back());
    }

    void transponse() {
        std::vector<int> newValues;
        std::vector<int> newColums;
        std::vector<int> newPointer;

        int index = 0;
        for (int i = 0; i < pointer.size() - 1; i++) {
            for (int j = 0; j < colums.size(); j++) {
                if (newPointer.size() == i) {
                    newPointer.push_back(index);
                }
                if (colums.at(j) == i) {
                    newValues.push_back(values.at(j));
                    for (int col = 0; col < pointer.size() - 1; col++) {
                        if (j >= pointer.at(col) && j < pointer.at(col + 1)) {
                            newColums.push_back(col);
                        }
                    }
                    index++;
                }
            }
        }

        newPointer.push_back(newValues.size());
        values = newValues;
        colums = newColums;
        pointer = newPointer;
    }

    friend bool operator==(const Matrix& lhs, const Matrix& rhs) {
        for (int i = 0; i < rhs.values.size(); i++) {
            if (lhs.values.at(i) != rhs.values.at(i)) return false;
        }
        for (int i = 0; i < rhs.colums.size(); i++) {
            if (lhs.colums.at(i) != rhs.colums.at(i)) return false;
        }
        for (int i = 0; i < rhs.pointer.size(); i++) {
            if (lhs.pointer.at(i) != rhs.pointer.at(i)) return false;
        }
        return true;
    }
};

Matrix omp_crs_mult(Matrix A, Matrix B);

#endif  // MODULES_TASK_2_MOKROUSOV_A_CRS_MULT_MATRIX_OMP_MOKROUSOV_A_CRS_MULT_MATRIX_OMP_H_
