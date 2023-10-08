// Copyright 2023 Binko Alexandr
#include <gtest/gtest.h>

#include "./kanon.h"

TEST(CannonTest, test_1) {
  int size = 16;
  Matrix matrix1(size);
  Matrix matrix2(size);
  std::vector<std::vector<double>> res_matrix;
  int block_size = size / 4;
  int block_count = size / block_size;

  for (int i = 0; i < size; ++i) {
    std::vector<double> vec(size);
    res_matrix.push_back(vec);
    for (int j = 0; j < size; ++j) {
      res_matrix[i][j] = 0;
    }
  }

  double num1 = 1.076, num2 = 2.067;
  matrix1.fillNewMatrix(num1);
  matrix2.fillNewMatrix(num2);
  Matrix matrix1_copy2(matrix1.get_matrix(), size);

  Matrix matrix3(
      matrix1.seqKanonAlg(matrix2, res_matrix, block_size, block_count), size);
  Matrix matrix4(matrix1_copy2.ompKanonAlg(matrix2, 4, res_matrix, block_size,
                                           block_count),
                 size);

  std::vector<std::vector<double>> matr1 = matrix3.get_matrix(),
                                   matr2 = matrix4.get_matrix();

  ASSERT_DOUBLE_EQ(matr1[1][1], matr2[1][1]);
}

TEST(CannonTest, test_2) {
  int size = 4;
  Matrix matrix1(size);
  Matrix matrix2(size);
  std::vector<std::vector<double>> res_matrix;
  int block_size = size / 2;
  int block_count = size / block_size;

  for (int i = 0; i < size; ++i) {
    std::vector<double> vec(size);
    res_matrix.push_back(vec);
    for (int j = 0; j < size; ++j) {
      res_matrix[i][j] = 0;
    }
  }

  double num1 = 1.076, num2 = 2.067;
  matrix1.fillNewMatrix(num1);
  matrix2.fillNewMatrix(num2);
  Matrix matrix1_copy2(matrix1.get_matrix(), size);

  Matrix matrix3(
      matrix1.seqKanonAlg(matrix2, res_matrix, block_size, block_count), size);
  Matrix matrix4(matrix1_copy2.ompKanonAlg(matrix2, 2, res_matrix, block_size,
                                           block_count),
                 size);

  std::vector<std::vector<double>> matr1 = matrix3.get_matrix(),
                                   matr2 = matrix4.get_matrix();
  ASSERT_DOUBLE_EQ(matr1[0][0], matr2[0][0]);
}

TEST(CannonTest, test_3) {
  int size = 4;
  Matrix matrix1(size);
  Matrix matrix2(size);
  std::vector<std::vector<double>> res_matrix;
  int block_size = size / 2;
  int block_count = size / block_size;

  for (int i = 0; i < size; ++i) {
    std::vector<double> vec(size);
    res_matrix.push_back(vec);
    for (int j = 0; j < size; ++j) {
      res_matrix[i][j] = 0;
    }
  }

  double num1 = 1.076, num2 = 2.067;
  matrix1.fillNewMatrix(num1);
  matrix2.fillNewMatrix(num2);
  Matrix matrix1_copy2(matrix1.get_matrix(), size);

  Matrix matrix3(
      matrix1.seqKanonAlg(matrix2, res_matrix, block_size, block_count), size);
  Matrix matrix4(matrix1_copy2.ompKanonAlg(matrix2, 2, res_matrix, block_size,
                                           block_count),
                 size);

  std::vector<std::vector<double>> matr1 = matrix3.get_matrix(),
                                   matr2 = matrix4.get_matrix();
  ASSERT_DOUBLE_EQ(matr1[size - 1][size - 1], matr2[size - 1][size - 1]);
}

TEST(CannonTest, test_4) {
  int size = 4;
  Matrix matrix1(size);
  Matrix matrix2(size);
  std::vector<std::vector<double>> res_matrix;
  int block_size = size / 2;
  int block_count = size / block_size;

  for (int i = 0; i < size; ++i) {
    std::vector<double> vec(size);
    res_matrix.push_back(vec);
    for (int j = 0; j < size; ++j) {
      res_matrix[i][j] = 0;
    }
  }

  double num1 = 1.076, num2 = 2.067;
  matrix1.fillNewMatrix(num1);
  matrix2.fillNewMatrix(num2);
  Matrix matrix1_copy2(matrix1.get_matrix(), size);

  Matrix matrix3(
      matrix1.seqKanonAlg(matrix2, res_matrix, block_size, block_count), size);
  Matrix matrix4(matrix1_copy2.ompKanonAlg(matrix2, 2, res_matrix, block_size,
                                           block_count),
                 size);

  std::vector<std::vector<double>> matr1 = matrix3.get_matrix(),
                                   matr2 = matrix4.get_matrix();

  for (int j(0); j < size; ++j) {
    ASSERT_DOUBLE_EQ(matr1[0][j], matr2[0][j]);
  }
}

TEST(CannonTest, test_5) {
  int size = 9;
  Matrix matrix1(size);
  Matrix matrix2(size);
  std::vector<std::vector<double>> res_matrix;
  int block_size = size / 3;
  int block_count = size / block_size;

  for (int i = 0; i < size; ++i) {
    std::vector<double> vec(size);
    res_matrix.push_back(vec);
    for (int j = 0; j < size; ++j) {
      res_matrix[i][j] = 0;
    }
  }

  double num1 = 1.076, num2 = 2.067;
  matrix1.fillNewMatrix(num1);
  matrix2.fillNewMatrix(num2);
  Matrix matrix1_copy2(matrix1.get_matrix(), size);

  Matrix matrix3(
      matrix1.seqKanonAlg(matrix2, res_matrix, block_size, block_count), size);
  Matrix matrix4(matrix1_copy2.ompKanonAlg(matrix2, 3, res_matrix, block_size,
                                           block_count),
                 size);

  std::vector<std::vector<double>> matr1 = matrix3.get_matrix(),
                                   matr2 = matrix4.get_matrix();

  for (int i(0); i < size; ++i) {
    for (int j(0); j < size; ++j) {
      ASSERT_DOUBLE_EQ(matr1[i][j], matr2[i][j]);
    }
  }
}
