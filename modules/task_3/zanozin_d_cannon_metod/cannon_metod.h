// Copyright 2023 Zanozin Danila
#ifndef MODULES_TASK_3_ZANOZIN_D_CANNON_METOD_CANNON_METOD_H_
#define MODULES_TASK_3_ZANOZIN_D_CANNON_METOD_CANNON_METOD_H_

#include <gtest/gtest.h>
#include <tbb/tbb.h>

#include <iostream>
#include <random>
#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix CreateRandomMatrix(const int n);
void ExpectMatricesNear(const Matrix &A, const Matrix &B, size_t N);

Matrix MultMat(const Matrix &A, const Matrix &B, size_t N);

Matrix SeqCannonMult(const Matrix &A, const Matrix &B, size_t blocksNum,
                     size_t blockSize, size_t N);

Matrix TBBCannonMult(const Matrix &A, const Matrix &B, size_t blocksNum,
                     size_t blockSize, size_t N);

#endif  // MODULES_TASK_3_ZANOZIN_D_CANNON_METOD_CANNON_METOD_H_
