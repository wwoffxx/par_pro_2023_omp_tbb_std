// Copyright 2023 Binko Alexandr
#include <gtest/gtest.h>

#include "./kanon.h"

TEST(KanonTest, test_1) {
  size_t size = 16;
  Matrix matrix1(size);
  Matrix matrix2(size);
  std::vector<std::vector<double>> res_matrix;
  size_t block_size = size / 4;
  size_t block_count = size / block_size;

  for (size_t i = 0; i < size; ++i) {
    std::vector<double> vec(size);
    res_matrix.push_back(vec);
    for (size_t j = 0; j < size; ++j) {
      res_matrix[i][j] = 0;
    }
  }
  double num1 = 1.076, num2 = 2.067;
  matrix1.fillNewMatrix(num1);
  matrix2.fillNewMatrix(num2);

  Matrix matrix3(matrix1.multiplyByMatrix(matrix2), size);

  Matrix matrix4(matrix1.KanonAlg(matrix2, res_matrix, block_size, block_count),
                 size);

  std::vector<std::vector<double>> matr1 = matrix3.get_matrix(),
                                   matr2 = matrix4.get_matrix();

  ASSERT_DOUBLE_EQ(matr1[1][1], matr2[1][1]);
}
TEST(KanonTest, test_2) {
  size_t size = 4;
  Matrix matrix1(size);
  Matrix matrix2(size);
  std::vector<std::vector<double>> res_matrix;
  size_t block_size = size / 2;
  size_t block_count = size / block_size;

  for (size_t i = 0; i < size; ++i) {
    std::vector<double> vec(size);
    res_matrix.push_back(vec);
    for (size_t j = 0; j < size; ++j) {
      res_matrix[i][j] = 0;
    }
  }

  double num1 = 1.076, num2 = 2.067;
  matrix1.fillNewMatrix(num1);
  matrix2.fillNewMatrix(num2);

  Matrix matrix3(matrix1.multiplyByMatrix(matrix2), size);
  Matrix matrix4(matrix1.KanonAlg(matrix2, res_matrix, block_size, block_count),
                 size);

  std::vector<std::vector<double>> matr1 = matrix3.get_matrix(),
                                   matr2 = matrix4.get_matrix();
  ASSERT_DOUBLE_EQ(matr1[0][0], matr2[0][0]);
}

TEST(KanonTest, test_3) {
  size_t size = 4;
  Matrix matrix1(size);
  Matrix matrix2(size);
  std::vector<std::vector<double>> res_matrix;
  size_t block_size = size / 2;
  size_t block_count = size / block_size;

  for (size_t i = 0; i < size; ++i) {
    std::vector<double> vec(size);
    res_matrix.push_back(vec);
    for (size_t j = 0; j < size; ++j) {
      res_matrix[i][j] = 0;
    }
  }

  double num1 = 1.076, num2 = 2.067;
  matrix1.fillNewMatrix(num1);
  matrix2.fillNewMatrix(num2);

  Matrix matrix3(matrix1.multiplyByMatrix(matrix2), size);
  Matrix matrix4(matrix1.KanonAlg(matrix2, res_matrix, block_size, block_count),
                 size);

  std::vector<std::vector<double>> matr1 = matrix3.get_matrix(),
                                   matr2 = matrix4.get_matrix();

  ASSERT_DOUBLE_EQ(matr1[size - 1][size - 1], matr2[size - 1][size - 1]);
}

TEST(KanonTest, test_4) {
  size_t size = 4;
  Matrix matrix1(size);
  Matrix matrix2(size);
  std::vector<std::vector<double>> res_matrix;
  size_t block_size = size / 2;
  size_t block_count = size / block_size;

  for (size_t i = 0; i < size; ++i) {
    std::vector<double> vec(size);
    res_matrix.push_back(vec);
    for (size_t j = 0; j < size; ++j) {
      res_matrix[i][j] = 0;
    }
  }

  double num1 = 1.076, num2 = 2.067;
  matrix1.fillNewMatrix(num1);
  matrix2.fillNewMatrix(num2);

  Matrix matrix3(matrix1.multiplyByMatrix(matrix2), size);
  Matrix matrix4(matrix1.KanonAlg(matrix2, res_matrix, block_size, block_count),
                 size);

  std::vector<std::vector<double>> matr1 = matrix3.get_matrix(),
                                   matr2 = matrix4.get_matrix();

  for (size_t j(0); j < size; ++j) {
    ASSERT_DOUBLE_EQ(matr1[0][j], matr2[0][j]);
  }
}

TEST(KanonTest, test_5) {
  size_t size = 9;
  Matrix matrix1(size);
  Matrix matrix2(size);
  std::vector<std::vector<double>> res_matrix;
  size_t block_size = size / 3;
  size_t block_count = size / block_size;

  for (size_t i = 0; i < size; ++i) {
    std::vector<double> vec(size);
    res_matrix.push_back(vec);
    for (size_t j = 0; j < size; ++j) {
      res_matrix[i][j] = 0;
    }
  }

  double num1 = 1.076, num2 = 2.067;
  matrix1.fillNewMatrix(num1);
  matrix2.fillNewMatrix(num2);

  Matrix matrix3(matrix1.multiplyByMatrix(matrix2), size);
  Matrix matrix4(matrix1.KanonAlg(matrix2, res_matrix, block_size, block_count),
                 size);

  std::vector<std::vector<double>> matr1 = matrix3.get_matrix(),
                                   matr2 = matrix4.get_matrix();

  for (size_t i(0); i < size; ++i) {
    for (size_t j(0); j < size; ++j) {
      ASSERT_DOUBLE_EQ(matr1[i][j], matr2[i][j]);
    }
  }
}
