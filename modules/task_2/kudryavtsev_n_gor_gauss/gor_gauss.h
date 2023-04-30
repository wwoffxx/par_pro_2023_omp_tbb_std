// Copyright 2023 Kudryavtsev Nikita
#ifndef MODULES_TASK_2_KUDRYAVTSEV_N_GOR_GAUSS_GOR_GAUSS_H_
#define MODULES_TASK_2_KUDRYAVTSEV_N_GOR_GAUSS_GOR_GAUSS_H_
#include<vector>
#include<iostream>
#include<ctime>
#include<random>
#include<algorithm>
using Matrix = std::vector<std::vector<double>>;
Matrix getRandomMatrix(int rows, int cols);
template <class T> T clamp(T tmp, int max, int min);
Matrix genMatrixKernel(int radius, double alpha);
Matrix SequentialGausFilter(Matrix img, int rows, int cols,
    int radius, double alpha);
Matrix ParallelGausFilter(Matrix img, int rows, int cols,
    int radius, double alpha);
void printMatrix(Matrix img, int rows, int cols);

#endif  // MODULES_TASK_2_KUDRYAVTSEV_N_GOR_GAUSS_GOR_GAUSS_H_
