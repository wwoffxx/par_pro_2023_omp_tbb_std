// Copyright 2023 Popov Andrey
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <cmath>
#include "../../../3rdparty/unapproved/unapproved.h"
#include "../popov_fox_std/popov_fox_std.h"

TEST(STD_Fox, Throws_On_NonEqual_Matrix) {
  auto X = getrandM(5);
  auto Y = getrandM(6);

  ASSERT_ANY_THROW(algorhythm_fox_parallel(X, Y));
}

TEST(STD_Fox, Parallel_Implementation_Is_Correct3x3) {
  Matrix M1 = {{1.5, 1.5, 1.5}, {2.7, 2.7, 2.7}, {3.6, 3.6, 3.6}};
  Matrix M2 = {{3.5, 3.5, 3.5}, {5.7, 5.7, 5.7}, {9.6, 9.6, 9.6}};
  Matrix ans = {
      {28.2, 28.2, 28.2}, {50.76, 50.76, 50.76}, {67.68, 67.68, 67.68}};
  auto result = algorhythm_fox_parallel(M1, M2);

  ASSERT_EQ(matrixchecking(result, ans), true);
}

TEST(STD_Fox, Parallel_And_Artless_The_Same_Answer4x4) {
  auto M1 = getrandM(4);
  auto M2 = getrandM(4);

  auto result1 = artlessmultiply(M1, M2);
  auto result2 = algorhythm_fox_parallel(M1, M2);

  ASSERT_TRUE(matrixchecking(result1, result2));
}

TEST(STD_Fox, Parallel_And_Module_The_Same_Answer4x4) {
  auto M1 = getrandM(4);
  auto M2 = getrandM(4);

  auto result1 = modularmultiply(M1, M2);

  auto result2 = algorhythm_fox_parallel(M1, M2);

  ASSERT_TRUE(matrixchecking(result1, result2));
}

TEST(STD_Fox, Parallel_And_Artless_The_Same_Answer15x15) {
  auto M1 = getrandM(15);
  auto M2 = getrandM(15);

  auto result1 = artlessmultiply(M1, M2);
  auto result2 = algorhythm_fox_parallel(M1, M2);

  ASSERT_TRUE(matrixchecking(result1, result2));
}

TEST(STD_Fox, Parallel_And_Module_The_Same_Answer15x15) {
  auto M1 = getrandM(15);
  auto M2 = getrandM(15);

  auto result1 = modularmultiply(M1, M2);
  auto result2 = algorhythm_fox_parallel(M1, M2);
  ASSERT_TRUE(matrixchecking(result1, result2));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
