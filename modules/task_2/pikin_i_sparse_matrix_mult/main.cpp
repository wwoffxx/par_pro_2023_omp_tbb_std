// Copyright 2023 Pikin Ilya
#include <gtest/gtest.h>
#include "./sparse_matrix_mult.h"

using cmp = std::complex<double>;

TEST(OMP_version, Dense_int_matrices_3x3_product_test) {
  std::vector<std::vector<cmp>> A = {{cmp(1, 0), cmp(0, 0), cmp(6, 0)},
                                     {cmp(8, 0), cmp(9, 0), cmp(-2, 0)},
                                     {cmp(-5, 0), cmp(1, 0), cmp(3, 0)}};
  std::vector<std::vector<cmp>> B = {{cmp(1, 0), cmp(4, 0), cmp(7, 0)},
                                     {cmp(2, 0), cmp(5, 0), cmp(8, 0)},
                                     {cmp(3, 0), cmp(6, 0), cmp(9, 0)}};
  std::vector<std::vector<cmp>> C = {{cmp(19, 0), cmp(40, 0), cmp(61, 0)},
                                     {cmp(20, 0), cmp(65, 0), cmp(110, 0)},
                                     {cmp(6, 0), cmp(3, 0), cmp(0, 0)}};

  CRSMatrix crsA(A), crsB(B), crsC(C);
  CRSMatrix prod = getProductOMP(crsA, crsB);

  ASSERT_EQ(crsC, prod);
}

TEST(OMP_version, Sparse_int_matrices_4x4_product_test) {
  std::vector<std::vector<cmp>> A = {
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(1, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(2, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(3, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(4, 0), cmp(0, 0)}};
  std::vector<std::vector<cmp>> B = {
      {cmp(0, 0), cmp(5, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(6, 0)},
      {cmp(7, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(8, 0), cmp(0, 0), cmp(0, 0)}};
  std::vector<std::vector<cmp>> C = {
      {cmp(0, 0), cmp(8, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(16, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(21, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(28, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)}};
  CRSMatrix crsA(A), crsB(B), crsC(C);
  CRSMatrix prod = getProductOMP(crsA, crsB);

  ASSERT_EQ(crsC, prod);
}

TEST(OMP_version, Sparse_complex_matrices_4x4_product_test) {
  std::vector<std::vector<cmp>> A = {
      {cmp(0, 0), cmp(2, -1.5), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(5.2, 4), cmp(0, 0)},
      {cmp(1.2, 0.8), cmp(0, 0), cmp(3.1, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(3.6, -1.7)}};
  std::vector<std::vector<cmp>> B = {
      {cmp(2.7, -1), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(1.5, -1)},
      {cmp(-4.3, 1.6), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0.5, 2), cmp(0, 0)}};
  std::vector<std::vector<cmp>> C = {
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(1.5, -4.25)},
      {cmp(-28.76, -8.88), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(-9.29, 5.92), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(5.2, 6.35), cmp(0, 0)}};
  CRSMatrix crsA(A), crsB(B), crsC(C);
  CRSMatrix prod = getProductOMP(crsA, crsB);

  ASSERT_EQ(crsC, prod);
}

TEST(OMP_version, Dense_complex_matrices_4x4_product_test) {
  std::vector<std::vector<cmp>> A = {
      {cmp(1, 0), cmp(2, -1.5), cmp(7, 0), cmp(9, 0)},
      {cmp(2, 0), cmp(4, 0), cmp(5.2, 4), cmp(10, 0)},
      {cmp(1.2, 0.8), cmp(5, 0), cmp(3.1, 0), cmp(11, 0)},
      {cmp(3, 0), cmp(6, 0), cmp(8, 0), cmp(3.6, -1.7)}};
  std::vector<std::vector<cmp>> B = {
      {cmp(2.7, -1), cmp(3, 0), cmp(7, 0), cmp(10, 0)},
      {cmp(1, 0), cmp(4, 0), cmp(8, 0), cmp(1.5, -1)},
      {cmp(-4.3, 1.6), cmp(5, 0), cmp(9, 0), cmp(11, 0)},
      {cmp(2, 0), cmp(6, 0), cmp(0.5, 2), cmp(12, 0)}};
  std::vector<std::vector<cmp>> C = {
      {cmp(-7.4, 8.7), cmp(100, -6), cmp(90.5, 6), cmp(196.5, -4.25)},
      {cmp(0.64, -10.88), cmp(108, 20), cmp(97.8, 56), cmp(203.2, 40)},
      {cmp(17.71, 5.92), cmp(105.1, 2.4), cmp(81.8, 27.6), cmp(185.6, 3)},
      {cmp(-13.1, 6.4), cmp(94.6, -10.2), cmp(146.2, 6.35), cmp(170.2, -26.4)}};
  CRSMatrix crsA(A), crsB(B), crsC(C);
  CRSMatrix prod = getProductOMP(crsA, crsB);

  ASSERT_EQ(crsC, prod);
}

TEST(OMP_version, Multiplication_by_zero_matrix_test) {
  std::vector<std::vector<cmp>> A = {
      {cmp(1, 0), cmp(2, -1.5), cmp(7, 0), cmp(9, 0)},
      {cmp(2, 0), cmp(4, 0), cmp(5.2, 4), cmp(10, 0)},
      {cmp(1.2, 0.8), cmp(5, 0), cmp(3.1, 0), cmp(11, 0)},
      {cmp(3, 0), cmp(6, 0), cmp(8, 0), cmp(3.6, -1.7)}};
  std::vector<std::vector<cmp>> B = {
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)},
      {cmp(0, 0), cmp(0, 0), cmp(0, 0), cmp(0, 0)}};
  CRSMatrix crsA(A), crsB(B);
  CRSMatrix prod = getProductOMP(crsA, crsB);

  ASSERT_EQ(crsB, prod);
}

TEST(OMP_version, Comparison_of_Seq_and_OMP_version) {
  CRSMatrix A, B, C, D;
  A = getRandCRSMatrix(100, 4);
  B = getRandCRSMatrix(100, 6);
  C = getProductSeq(A, B);
  D = getProductOMP(A, B);

  ASSERT_EQ(C, D);
}

// TEST(OMP_version, Time_test) {
// CRSMatrix A = getRandCRSMatrix(10000, 50);
// CRSMatrix B = getRandCRSMatrix(10000, 50);
// double start_time = omp_get_wtime();
// CRSMatrix C = getProductSeq(A, B);
// double end_time = omp_get_wtime();
// double search_time = end_time - start_time;
// std::cout << "getProductSeq() time: " << search_time << " seconds\n";
// start_time = omp_get_wtime();
// CRSMatrix D = getProductOMP(A, B);
// end_time = omp_get_wtime();
// search_time = end_time - start_time;
// std::cout << "getProductOMP() time: " << search_time << " seconds\n";
// ASSERT_EQ(C, D);
//}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
