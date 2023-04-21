// Copyright 2023 Artemev Alexej
#include <gtest/gtest.h>
#include "./artemev_alexej_conj_grad.h"

TEST(CONJ_GRAD, TEST_2x2) {
    std::vector<std::vector<double>> A = { { 1, 3}, {3, 8} };
    std::vector<double> betta = { 4, 5 };
    std::vector<double> result = { -17, 7 };
    std::vector<double> decision = conj_grad_method(A, betta);

    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_NEAR(decision[i], result[i], 0.5);
    }
}

TEST(CONJ_GRAD, TEST_3x3) {
    std::vector<std::vector<double>> A = { { 3, 4, 0}, {4, -3, 0}, {0, 0, 5} };
    std::vector<double> betta = { 1, 5, 9 };
    std::vector<double> result = { 0.92, -0.44, 1.8 };
    std::vector<double> decision = conj_grad_method(A, betta);

    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_NEAR(decision[i], result[i], 0.5);
    }
}

TEST(CONJ_GRAD, TEST2_3x3) {
    std::vector<std::vector<double>> A = { { 3.2, -1.7, 2.5}, {1.5, 6.2, -2.9}, {2.8, -1.7, 3.8} };
    std::vector<double> betta = { 3.7, 3.2, 2.8 };
    std::vector<double> result = { 2.094, -0.465, -1.015 };
    std::vector<double> decision = conj_grad_method(A, betta);

    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_NEAR(decision[i], result[i], 0.5);
    }
}

TEST(CONJ_GRAD, TEST_4x4) {
    std::vector<std::vector<double>> A = { {5, 4, 0, 3},
                                           {4, 6, 1, 5},
                                           {0, 1, 0, 1},
                                           {3, 5, 1, 5},
                                           {6, 7, 1, 6}, };
    std::vector<double> betta = { 6, 7, 1, 6 };

    std::vector<double> x = conj_grad_method(A, betta);
    std::vector<double> result = { 0.5, 0.5, -0.5, 0.5 };
    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_NEAR(x[i], result[i], 0.5);
    }
}

TEST(CONJ_GRAD, TEST_5x5) {
    std::vector<std::vector<double>> A = { {5, 4, 0, 3, 6},
                                           {4, 6, 1, 5, 7},
                                           {0, 1, 0, 1, 1},
                                           {3, 5, 1, 5, 6},
                                           {6, 7, 1, 6, 10}, };
    std::vector<double> betta = { 2, 5, 0, 9, 1 };

    std::vector<double> x = conj_grad_method(A, betta);
    std::vector<double> result = { 5, -2, 1, 9, -7 };
    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_NEAR(x[i], result[i], 0.5);
    }
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
