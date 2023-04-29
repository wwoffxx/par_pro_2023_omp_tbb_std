// Copyright 2023 Shvandyreva Alina
#include "../../../modules/task_1/shvandyreva_a_fox_algorithm/fox_algorithm.h"

static matrix sum_block(const matrix& A, const matrix& B) {
    matrix result(A.size(), std::vector<double>(A[0].size()));
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

static matrix multiply_block(const matrix& A, const matrix& B) {
    matrix result(A.size(), std::vector<double>(B[0].size()));
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            result[i][j] = 0;
            for (int k = 0; k < A[0].size(); k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

matrix generate_matrix(size_t x_size, size_t y_size) {
    matrix result(y_size, std::vector<double>(x_size));
    std::random_device device;
    std::mt19937 mt(device());
    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            result[y][x] = 0.1 * (mt() % 1000);
        }
    }
    return result;
}

matrix generate_identity_matrix(size_t size) {
    matrix result(size, std::vector<double>(size));
    for (int i = 0; i < size; i++) {
        result[i][i] = 1;
    }
    return result;
}

matrix seq_multiply(const matrix& A, const matrix& B) {
    return multiply_block(A, B);
}
