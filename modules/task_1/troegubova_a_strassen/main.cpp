// Copyright 2023 Troegubova Alexandra
#include <gtest/gtest.h>
#include <vector>
#include "./strassen.h"

TEST(Strassen_seq, Incorrect_matrix_size) {
    int n = 14;
    std::vector<double> A = getRandomMatrix(n);
    std::vector<double> B = getRandomMatrix(n);
    ASSERT_THROW(multiplyStrassenSeq(A, B),
        std::invalid_argument);
}

TEST(Strassen_seq, Correct_finding_of_the_multiply_of_matrix_with_dimension_8x8) {
    int n = 8;
    std::vector<double> A = getRandomMatrix(n);
    std::vector<double> B = getRandomMatrix(n);
    ASSERT_EQ(multiplyStrassenSeq(A, B), multiplyNaive(A, B));
}

TEST(Strassen_seq, Correct_finding_of_the_multiply_of_matrix_with_dimension_16x16) {
    int n = 16;
    std::vector<double> A = getRandomMatrix(n);
    std::vector<double> B = getRandomMatrix(n);
    ASSERT_EQ(multiplyStrassenSeq(A, B), multiplyNaive(A, B));
}

TEST(Strassen_seq, Correct_finding_of_the_multiply_of_matrix_with_dimension_32x32) {
    int n = 32;
    std::vector<double> A = getRandomMatrix(n);
    std::vector<double> B = getRandomMatrix(n);
    ASSERT_EQ(multiplyStrassenSeq(A, B), multiplyNaive(A, B));
}

TEST(Strassen_seq, Correct_finding_of_the_multiply_of_matrix_with_dimension_128x128) {
    int n = 128;
    std::vector<double> A = getRandomMatrix(n);
    std::vector<double> B = getRandomMatrix(n);
    ASSERT_EQ(multiplyStrassenSeq(A, B), multiplyNaive(A, B));
}