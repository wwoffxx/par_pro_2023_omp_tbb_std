// Copyright 2023 Nikolaev Alexander
#include <gtest/gtest.h>
#include "./sparse_matrix.h"

TEST(Sparse_Matrix_Mult, Test_Mult1) {
    CCSMatrix A;
    CCSMatrix B;
    CCSMatrix C;
    std::vector<std::vector<Complex>> matrixA = { {0, 8, 0},
                                                  {1, 0, 2},
                                                  {0, 0, 6}};

    std::vector<std::vector<Complex>> matrixB = { {0, 8, 4},
                                                  {0, 0, 7},
                                                  {5, 0, 0}};
    std::vector<Complex> result = { 56, 10, 8, 4, 30 };
    A = MatrixtoCCSMatrix(matrixA);
    B = MatrixtoCCSMatrix(matrixB);
    TransposeMatrix(&A);
    C = Multiplicate(A, B);
    ASSERT_EQ(C.value, result);
}

TEST(Sparse_Matrix_Mult, Test_Mult2) {
    CCSMatrix A;
    CCSMatrix B;
    CCSMatrix C;
    std::vector<std::vector<Complex>> matrixA = { {0, 8, 0, 8},
                                                  {1, 0, 2, 0},
                                                  {0, 0, 6, 0},
                                                  {4, 5, 0, 9} };

    std::vector<std::vector<Complex>> matrixB = { {0, 8, 4, 0},
                                                  {0, 0, 7, 8},
                                                  {5, 0, 0, 0},
                                                  {0, 1, 0, 7} };
    std::vector<Complex> result = { 8, 56, 120, 10, 8, 4, 30, 41, 51, 103 };
    A = MatrixtoCCSMatrix(matrixA);
    B = MatrixtoCCSMatrix(matrixB);
    TransposeMatrix(&A);
    C = Multiplicate(A, B);
    ASSERT_EQ(C.value, result);
}

TEST(Sparse_Matrix_Mult, Test_Mult3) {
    CCSMatrix A;
    CCSMatrix B;
    CCSMatrix C;
    std::vector<std::vector<Complex>> matrixA = { {0, 8, 0, 0, 1, 0},
                                                {0, 0, 7, 0, 0, 4},
                                                {5, 0, 0, 3, 0, 0},
                                                {0, 2, 0, 0, 1, 7},
                                                {0, 6, 3, 0, 0, 1},
                                                {4, 0, 0, 1, 0, 0} };

    std::vector<std::vector<Complex>> matrixB = { {0, 8, 0, 0, 1, 0},
                                                {0, 0, 7, 0, 0, 4},
                                                {5, 0, 0, 3, 0, 0},
                                                {0, 2, 0, 0, 1, 7},
                                                {0, 6, 3, 0, 0, 1},
                                                {4, 0, 0, 1, 0, 0} };
    std::vector<Complex> result = { 6, 59, 33, 51, 25, 46, 8, 21, 28, 6, 17, 7, 9, 19, 42, 10, 24, 34, 5, 7 };
    A = MatrixtoCCSMatrix(matrixA);
    B = MatrixtoCCSMatrix(matrixB);
    TransposeMatrix(&A);
    C = Multiplicate(A, B);
    ASSERT_EQ(C.value, result);
}

TEST(Sparse_Matrix_Mult, Test_Mult4) {
    CCSMatrix A;
    CCSMatrix B;
    CCSMatrix C;
    A = GetRandomMatrix(10, 20);
    B = GetRandomMatrix(10, 20);
    TransposeMatrix(&A);
    C = Multiplicate(A, B);
}

TEST(Sparse_Matrix_Mult, Test_Mult5) {
    CCSMatrix A;
    CCSMatrix B;
    CCSMatrix C;
    A = GetRandomMatrix(20, 50);
    B = GetRandomMatrix(20, 50);
    TransposeMatrix(&A);
    C = Multiplicate(A, B);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
