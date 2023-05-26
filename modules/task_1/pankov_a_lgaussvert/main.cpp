// Copyright 2023 Pankov Anatoliy
#include <gtest/gtest.h>
#include <vector>
#include "./lgaussvert.h"


TEST(LGaussVertical, MatrixMN0Test) {
    int m = 0;
    int n = 0;
    std::vector<double> matrix(m * n);

    ASSERT_ANY_THROW(matrix = SeqGaussFilter(matrix, m, n));
}

TEST(LGaussVertical, ZeroMatrixTest3x3) {
    int m = 3;
    int n = 3;
    std::vector<double> matrix(0);

    ASSERT_ANY_THROW(matrix = SeqGaussFilter(matrix, m, n));
}

TEST(LGaussVertical, Test3x3) {
    int m = 3;
    int n = 3;
    std::vector<double> matrix(m * n);
    matrix[0] = 85;
    matrix[1] = 99;
    matrix[2] = 112;
    matrix[3] = 126;
    matrix[4] = 140;
    matrix[5] = 153;
    matrix[6] = 167;
    matrix[7] = 180;
    matrix[8] = 195;

    std::vector<double> answer(m * n);

    answer[0] = 96;
    answer[1] = 107;
    answer[2] = 117;
    answer[3] = 128;
    answer[4] = 139;
    answer[5] = 150;
    answer[6] = 161;
    answer[7] = 171;
    answer[8] = 183;

    matrix = SeqGaussFilter(matrix, m, n);

    ASSERT_EQ(matrix, answer);
}

TEST(LGaussVertical, RandomTest3x3) {
    int m = 3;
    int n = 3;
    std::vector<double> matrix = MakeRandomMatrix(m, n);

    ASSERT_NO_THROW(matrix = SeqGaussFilter(matrix, m, n));
}

TEST(LGaussVertical, RandomTest10x10) {
    int m = 10;
    int n = 10;
    std::vector<double> matrix = MakeRandomMatrix(m, n);

    ASSERT_NO_THROW(matrix = SeqGaussFilter(matrix, m, n));
}

TEST(LGaussVertical, RandomTest50x50) {
    int m = 50;
    int n = 50;
    std::vector<double> matrix = MakeRandomMatrix(m, n);

    ASSERT_NO_THROW(matrix = SeqGaussFilter(matrix, m, n));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
