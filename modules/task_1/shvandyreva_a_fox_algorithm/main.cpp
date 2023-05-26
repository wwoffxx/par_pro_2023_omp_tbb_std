// Copyright 2023 Shvandyreva Alina
#include <gtest/gtest.h>
#include "./fox_algorithm.h"

TEST(Seq_Mult, SimpleTest) {
    matrix A = { {2} };
    matrix B = { {3} };
    matrix expected = { {6} };
    matrix res = seq_multiply(A, B);
    ASSERT_EQ(res, expected);
}

TEST(Seq_Mult, Test_Long_By_Wide) {
    matrix A = { {1}, {2}, {3}, {4}, {5}, {6} };
    matrix B = { {6, 5, 4, 3, 2, 1} };
    matrix expected = {
        {6, 5, 4, 3, 2, 1},
        {12, 10, 8, 6, 4, 2},
        {18, 15, 12, 9, 6, 3},
        {24, 20, 16, 12, 8, 4},
        {30, 25, 20, 15, 10, 5},
        {36, 30, 24, 18, 12, 6}
    };
    matrix res = seq_multiply(A, B);
    ASSERT_EQ(res, expected);
}

TEST(Seq_Mult, Test_Wide_By_long) {
    matrix A = { {6, 5, 4, 3, 2, 1} };
    matrix B = { {1}, {2}, {3}, {4}, {5}, {6} };
    matrix expected = { {56} };
    matrix res = seq_multiply(A, B);
    ASSERT_EQ(res, expected);
}

TEST(Seq_Mult, Test_Quad_By_Quad) {
    matrix A = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    matrix B = { {10, 11, 12}, {13, 14, 15}, {16, 17, 18} };
    matrix expected = { {84, 90, 96}, {201, 216, 231}, {318, 342, 366} };
    matrix res = seq_multiply(A, B);
    ASSERT_EQ(res, expected);
}

TEST(Seq_Mult, Any_By_Identity) {
    matrix A = generate_matrix(5, 5);
    matrix E = generate_identity_matrix(5);
    matrix res = seq_multiply(A, E);
    ASSERT_EQ(res, A);
}
