// Copyright 2023 Troegubova Alexandra
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <string>
#include "../../../modules/task_1/troegubova_a_strassen/strassen.h"

std::vector<double> getRandomMatrix(int n) {
    std::mt19937 gen(std::random_device().operator()());
    std::uniform_int_distribution<> range(-20, 20);
    int matrix_size = n * n;
    std::vector<double> matrix(matrix_size);
    for (int i = 0; i < matrix_size; i++)
        matrix[i] = range(gen);
    return matrix;
}

std::vector<double> multiplyNaive(const std::vector<double>& A, const std::vector<double>& B) {
    int n = static_cast<int>(sqrt(A.size()));
    std::vector<double> res(A.size());
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                res[i * n + j] += A[i * n + k] * B[k * n + j];
    return res;
}

std::vector<double> sumMatrix(const std::vector<double>& A, const std::vector<double>& B) {
    int n = A.size();
    std::vector<double> res(n);
    for (int i = 0; i < n; ++i)
        res[i] = A[i] + B[i];
    return res;
}

std::vector<double> diffMatrix(const std::vector<double>& A, const std::vector<double>& B) {
    int n = A.size();
    std::vector<double> res(n);
    for (int i = 0; i < n; ++i)
        res[i] = A[i] - B[i];
    return res;
}

std::vector<std::vector<double>> getBlockMatrix(const std::vector<double>& A) {
    std::vector<std::vector<double>> res(4);
    int n = static_cast<int>(sqrt(A.size()));
    int block_size = n / 2;

    for (int i = 0; i < 4; i++) {
        std::vector<double> blok(block_size * block_size);
        for (int j = 0; j < block_size; j++) {
            for (int k = 0; k < block_size; k++)
                blok[j * block_size + k] = A[i < 2 ? j * n + k +
                block_size * (i % 2) : (j + block_size) * n + k + block_size * (i % 2)];
        }
        res[i] = blok;
    }
    return res;
}

std::vector<double> multiplyStrassenSeq(const std::vector<double>& A, const std::vector<double>& B) {
    int n = static_cast<int>(sqrt(A.size()));
    if ((n & (n - 1)) != 0)
        throw std::invalid_argument("not a power of two");

    int block_size = A.size() / 4;
    std::vector<double> res(A.size());
    if (block_size == 1) {
        double D = (A[0] + A[3]) * (B[0] + B[3]);
        double D1 = (A[1] - A[3]) * (B[2] + B[3]);
        double D2 = (A[2] - A[0]) * (B[0] + B[1]);
        double H1 = (A[0] + A[1]) * B[3];
        double H2 = (A[2] + A[3]) * B[0];
        double V1 = A[3] * (B[2] - B[0]);
        double V2 = A[0] * (B[1] - B[3]);

        res[0] = D + D1 + V1 - H1;
        res[1] = V2 + H1;
        res[2] = V1 + H2;
        res[3] = D + D2 + V2 - H2;

        return res;
    } else {
        std::vector<std::vector<double>> blockA = getBlockMatrix(A);
        std::vector<std::vector<double>> blockB = getBlockMatrix(B);

        std::vector<double> D = multiplyStrassenSeq(sumMatrix(blockA[0], blockA[3]),
            sumMatrix(blockB[0], blockB[3]));
        std::vector<double> D1 = multiplyStrassenSeq(diffMatrix(blockA[1], blockA[3]),
            sumMatrix(blockB[2], blockB[3]));
        std::vector<double> D2 = multiplyStrassenSeq(diffMatrix(blockA[2], blockA[0]),
            sumMatrix(blockB[0], blockB[1]));
        std::vector<double> H1 = multiplyStrassenSeq(sumMatrix(blockA[0], blockA[1]),
            blockB[3]);
        std::vector<double> H2 = multiplyStrassenSeq(sumMatrix(blockA[2], blockA[3]),
            blockB[0]);
        std::vector<double> V1 = multiplyStrassenSeq(blockA[3],
            diffMatrix(blockB[2], blockB[0]));
        std::vector<double> V2 = multiplyStrassenSeq(blockA[0],
            diffMatrix(blockB[1], blockB[3]));

        std::vector<double> block11(block_size);
        std::vector<double> block12(block_size);
        std::vector<double> block21(block_size);
        std::vector<double> block22(block_size);

        for (int i = 0; i < block_size; i++) {
            block11[i] = D[i] + D1[i] + V1[i] - H1[i];
            block12[i] = V2[i] + H1[i];
            block21[i] = V1[i] + H2[i];
            block22[i] = D[i] + D2[i] + V2[i] - H2[i];
        }
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < n / 2; j++) {
                res[i * n + j] = block11[i * n / 2 + j];
                res[i * n + n / 2 + j] = block12[i * n / 2 + j];
                res[(n * n / 2) + i * n + j] = block21[i * n / 2 + j];
                res[(n * n / 2) + i * n + n / 2 + j] = block22[i * n / 2 + j];
            }
        }
        return res;
    }
}
