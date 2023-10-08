// Copyright 2023 Binko Alexandr
#ifndef MODULES_TASK_1_BINKO_A_KANON_KANON_H_
#define MODULES_TASK_1_BINKO_A_KANON_KANON_H_
#include <iostream>
#include <vector>

class Matrix {
 public:
  explicit Matrix(size_t size) : size(size) {
    matrix.reserve(size);
    for (size_t i(0); i < size; ++i) {
      std::vector<double> vec(size);
      matrix.push_back(vec);
    }
  }
  Matrix(std::vector<std::vector<double>> matrix, size_t size) : size(size) {
    this->matrix.reserve(size);
    for (size_t i(0); i < size; ++i) {
      std::vector<double> vec;
      this->matrix.push_back(vec);
    }
    for (size_t i(0); i < size; ++i) {
      this->matrix[i].assign(matrix[i].begin(), matrix[i].end());
    }
  }
  ~Matrix() {}
  std::vector<std::vector<double>> get_matrix() { return matrix; }
  void fillNewMatrix(double num);
  std::vector<std::vector<double>> multiplyByMatrix(Matrix matrix);
  std::vector<std::vector<double>> KanonAlg(
      Matrix matrix2, std::vector<std::vector<double>> res_matrix,
      size_t block_size, size_t block_count);
  void toLeftSide(std::vector<std::vector<double>> *matr, size_t pos,
                  size_t block_count, size_t skew);
  void shiftUp(std::vector<std::vector<double>> *matr, size_t pos,
               size_t block_count, size_t skew);
  void mutiplyByBlock(std::vector<std::vector<double>> block1,
                      std::vector<std::vector<double>> block2,
                      std::vector<std::vector<double>> *res_block,
                      size_t shift_l, size_t shift_r, size_t skew);

 private:
  size_t size;
  std::vector<std::vector<double>> matrix;
};
#endif  // MODULES_TASK_1_BINKO_A_KANON_KANON_H_
