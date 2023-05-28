// Copyright 2023 Grachev Valentin
#include <gtest/gtest.h>
#include "../../../modules/task_1/grachev_v_mult_rare_matrix/mult_rare_matrix.h"


TEST(Mult_rare_matrix_sequential, Test_1_2x2_and_2x2) {
    double arr1[] = {1, 0, 3, 0};
    MatrixCRS matr1(2, 2);
    matr1.Fill(arr1);

    double arr2[] = {0, 3, 4, 0};
    MatrixCRS matr2(2, 2);
    matr2.Fill(arr2);

    double res[] = {0, 3, 0, 9};
    MatrixCRS resMatr(2, 2);
    resMatr.Fill(res);

    bool ans = matr1.Multiple(matr2).Equal(resMatr);

    EXPECT_EQ(ans, true);
}

TEST(Mult_rare_matrix_sequential, Test_2_3x4_and_4x3) {
    double arr1[] = {1, 0, 2, 0, 3, 0, 0, 2, 1, 2, 0, 5};
    MatrixCRS matr1(3, 4);
    matr1.Fill(arr1);

    double arr2[] = {1, 0, 2, 3, 0, 0, 1, 2, 0, 0, 1, 2};
    MatrixCRS matr2(4, 3);
    matr2.Fill(arr2);

    double res[] = {3, 4, 2, 3, 2, 10, 7, 5, 12};
    MatrixCRS resMatr(3, 3);
    resMatr.Fill(res);

    bool ans = matr1.Multiple(matr2).Equal(resMatr);

    EXPECT_EQ(ans, true);
}

TEST(Mult_rare_matrix_sequential, Test_3_4x2_and_2x4) {
    double arr1[] = {1, 0, 3, 4, 0, 3, 3, 0};
    MatrixCRS matr1(4, 2);
    matr1.Fill(arr1);

    double arr2[] = {1, 0, 2, 0, 3, 4, 0, 2};
    MatrixCRS matr2(2, 4);
    matr2.Fill(arr2);

    double res[] = {1, 0, 2, 0, 15, 16, 6, 8, 9, 12, 0, 6, 3, 0, 6, 0};
    MatrixCRS resMatr(4, 4);
    resMatr.Fill(res);
    bool ans = matr1.Multiple(matr2).Equal(resMatr);

    EXPECT_EQ(ans, true);
}

TEST(Mult_rare_matrix_sequential, Test_4_3x3_and_3x5) {
    double arr1[] = {1, 0, 0, 3, 4, 0, 0, 3, 0};
    MatrixCRS matr1(3, 3);
    matr1.Fill(arr1);

    double arr2[] = {1, 0, 2, 0, 1, -3, 4, 0, 0, 0, 1, 0, 0, -3, 0};
    MatrixCRS matr2(3, 5);
    matr2.Fill(arr2);

    double res[] = {1, 0, 2, 0, 1, -9, 16, 6, 0, 3, -9, 12, 0, 0, 0};
    MatrixCRS resMatr(3, 5);
    resMatr.Fill(res);

    bool ans = matr1.Multiple(matr2).Equal(resMatr);

    EXPECT_EQ(ans, true);
}

TEST(Mult_rare_matrix_sequential, Test_5_4x4_and_4x4) {
    double arr1[] = {1, 0, 0, 2, 0, 1, 2, 0, 0, 2, 1, 0, 2, 0, 0, 1};
    MatrixCRS matr1(4, 4);
    matr1.Fill(arr1);

    double arr2[] = {2, 0, 0, 1, 0, 2, 1, 0, 0, 1, 2, 0, 1, 0, 0, 2};
    MatrixCRS matr2(4, 4);
    matr2.Fill(arr2);

    double res[] = {4, 0, 0, 5, 0, 4, 5, 0, 0, 5, 4, 0, 5, 0, 0, 4};
    MatrixCRS resMatr(4, 4);
    resMatr.Fill(res);

    bool ans = matr1.Multiple(matr2).Equal(resMatr);

    EXPECT_EQ(ans, true);
}
