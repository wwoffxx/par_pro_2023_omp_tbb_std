// Copyright 2023 Mokrousov Artem
#ifndef MODULES_TASK_3_MOKROUSOV_A_CRS_MULT_MATRIX_TBB_CRS_MULT_MATRIX_TBB_H_
#define MODULES_TASK_3_MOKROUSOV_A_CRS_MULT_MATRIX_TBB_CRS_MULT_MATRIX_TBB_H_

#include <gtest/gtest.h>
#include <tbb/tbb.h>

#include <iostream>
#include <random>
#include <string>
#include <vector>

class CRSMatrix {
 public:
    int nRows;
    int nColumns;

    std::vector<double> values;
    std::vector<int> columns;
    std::vector<int> pointers;

    CRSMatrix(int nC, int nR, const std::vector<double>& v,
              const std::vector<int>& c, const std::vector<int>& p);
    explicit CRSMatrix(std::vector<std::vector<double>> mtx);
    explicit CRSMatrix(int nC = 0, int nR = 0);
    CRSMatrix T();
    CRSMatrix dot(CRSMatrix mtx);
    CRSMatrix tbbDot(CRSMatrix mtx);
    bool operator==(const CRSMatrix& mtx) const;
    void arraysPrint();
};

std::vector<std::vector<double>> genMatrix(int cols, int rows,
                                                double density);

std::vector<std::vector<double>> mulMatrix(std::vector<std::vector<double>> A,
                                            std::vector<std::vector<double>> B);

std::vector<std::vector<double>> zerpMatrix(int cols, int rows);
#endif  // MODULES_TASK_3_MOKROUSOV_A_CRS_MULT_MATRIX_TBB_CRS_MULT_MATRIX_TBB_H_
