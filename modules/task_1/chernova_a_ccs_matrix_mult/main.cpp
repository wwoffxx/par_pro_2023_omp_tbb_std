// Copyright 2023 Chernova Anna
#include <gtest/gtest.h>

#include <complex>
#include <vector>

#include "./ccs_matrix_mult.h"

TEST(Sequential, Test_Default_Constructor) {
  size_t rows = 3;
  size_t columns = 3;

  EXPECT_NO_THROW(MatrixCSS(rows, columns));
}

TEST(Sequential, Test_Constructor_With_Parameters) {
  size_t rows = 3;
  size_t columns = 3;
  std::vector<std::complex<double>> buff{
      std::complex<double>(0, 0), std::complex<double>(2, 0),
      std::complex<double>(3, 0), std::complex<double>(0, 0),
      std::complex<double>(0, 0), std::complex<double>(1, 0),
      std::complex<double>(0, 0), std::complex<double>(2, 0),
      std::complex<double>(0, 0)};

  EXPECT_NO_THROW(MatrixCSS(buff, rows, columns));
}

TEST(Sequential, Test_Copy_Constructor) {
  size_t rows = 3;
  size_t columns = 3;
  std::vector<std::complex<double>> buff{
      std::complex<double>(0, 0), std::complex<double>(2, 0),
      std::complex<double>(3, 0), std::complex<double>(0, 0),
      std::complex<double>(0, 0), std::complex<double>(1, 0),
      std::complex<double>(0, 0), std::complex<double>(2, 0),
      std::complex<double>(0, 0)};
  MatrixCSS matrix(buff, rows, columns);

  EXPECT_NO_THROW(MatrixCSS matrix2 = MatrixCSS(matrix));
}

TEST(Sequential, Test_Transponse) {
  size_t rows = 3;
  size_t columns = 3;
  std::vector<std::complex<double>> buff{
      std::complex<double>(0, 0), std::complex<double>(2, 0),
      std::complex<double>(3, 0), std::complex<double>(0, 0),
      std::complex<double>(0, 0), std::complex<double>(1, 0),
      std::complex<double>(0, 0), std::complex<double>(2, 0),
      std::complex<double>(0, 0)};

  MatrixCSS matrix = MatrixCSS(buff, rows, columns);

  EXPECT_NO_THROW(matrix.transponse());
}

TEST(Sequential, Test_Mult_3_3) {
  size_t rows = 3;
  size_t columns = 3;
  std::vector<std::complex<double>> buff_1{
      std::complex<double>(0, 0), std::complex<double>(2, 0),
      std::complex<double>(3, 0), std::complex<double>(0, 0),
      std::complex<double>(0, 0), std::complex<double>(1, 0),
      std::complex<double>(0, 0), std::complex<double>(2, 0),
      std::complex<double>(0, 0)};
  std::vector<std::complex<double>> buff_2{
      std::complex<double>(0, 0), std::complex<double>(0, 0),
      std::complex<double>(6, 0), std::complex<double>(0, 0),
      std::complex<double>(2, 0), std::complex<double>(3, 0),
      std::complex<double>(0, 0), std::complex<double>(0, 0),
      std::complex<double>(4, 0)};

  std::vector<std::complex<double>> result{
      std::complex<double>(0, 0),  std::complex<double>(4, 0),
      std::complex<double>(18, 0), std::complex<double>(0, 0),
      std::complex<double>(0, 0),  std::complex<double>(4, 0),
      std::complex<double>(0, 0),  std::complex<double>(4, 0),
      std::complex<double>(6, 0)};

  MatrixCSS matrix_1 =
      MatrixCSS(buff_1, rows, columns) * MatrixCSS(buff_2, rows, columns);
  MatrixCSS matrix_2 = MatrixCSS(result, rows, columns);

  ASSERT_TRUE(matrix_1 == matrix_2);
}
