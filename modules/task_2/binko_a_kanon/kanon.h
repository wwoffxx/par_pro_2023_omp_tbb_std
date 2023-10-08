// Copyright 2023 Binko Alexandr
#ifndef MODULES_TASK_2_BINKO_A_KANON_KANON_H_
#define MODULES_TASK_2_BINKO_A_KANON_KANON_H_
#include <omp.h>

#include <iostream>
#include <vector>

class Matrix {
 public:
  explicit Matrix(int size) : size(size) {
    matrix.reserve(size);
    for (int i(0); i < size; ++i) {
      std::vector<double> vec(size);
      matrix.push_back(vec);
    }
  }
  Matrix(std::vector<std::vector<double>> matrix, int size) : size(size) {
    this->matrix.reserve(size);
    for (int i(0); i < size; ++i) {
      std::vector<double> vec;
      this->matrix.push_back(vec);
    }
    for (int i(0); i < size; ++i) {
      this->matrix[i].assign(matrix[i].begin(), matrix[i].end());
    }
  }
  ~Matrix() {}
  std::vector<std::vector<double>> get_matrix() { return matrix; }
  void fillNewMatrix(double num);
  std::vector<std::vector<double>> seqKanAlg(
      Matrix matrix2, std::vector<std::vector<double>> res_matrix,
      int block_size, int block_count);
  std::vector<std::vector<double>> ompKanAlg(
      Matrix matrix2, int thread_nums,
      std::vector<std::vector<double>> res_matrix, int block_size,
      int block_count);
  void toLeftSide(std::vector<std::vector<double>> *matr, int pos,
                 int block_count, int skew);
  void shiftUp(std::vector<std::vector<double>> *matr, int pos, int block_count,
               int skew);
  void mutiplyByBlock(std::vector<std::vector<double>> block1,
                      std::vector<std::vector<double>> block2,
                      std::vector<std::vector<double>> *res_block, int shift_l,
                      int shift_r, int skew);

 private:
  int size;
  std::vector<std::vector<double>> matrix;
};
#endif  // MODULES_TASK_2_BINKO_A_KANON_KANON_H_
