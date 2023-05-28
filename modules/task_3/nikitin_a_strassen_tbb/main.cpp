// Copyright 2023 Nikitin Aleksandr
#include <gtest/gtest.h>

#include <vector>

#include "./strassen_tbb.h"

TEST(Nikitin_test, NaiveMultiplication) {
  double a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double b[16] = {2, 0, 1, 2, 1, 2, 1, 0, 0, 1, 2, 1, 2, 1, 0, 2};

  double expected[16] = {12, 11, 9,  13, 32, 27, 25, 33,
                         52, 43, 41, 53, 72, 59, 57, 73};

  double c[16];

  int size = 4;

  naive_mult(a, b, c, size);

  for (int i = 0; i < size * size; i++) {
    EXPECT_EQ(c[i], expected[i]);
  }
}

TEST(Nikitin_test, StrassenMultiplication) {
  double a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double b[16] = {2, 0, 1, 2, 1, 2, 1, 0, 0, 1, 2, 1, 2, 1, 0, 2};

  double expected[16] = {12, 11, 9,  13, 32, 27, 25, 33,
                         52, 43, 41, 53, 72, 59, 57, 73};

  double c[16];

  int size = 4;

  strassen(a, b, c, size);

  for (int i = 0; i < size * size; i++) {
    EXPECT_EQ(c[i], expected[i]);
  }
}

TEST(Nikitin_test, NegativeElements) {
  double a[16] = {-1, -2,  -3,  -4,  -5,  -6,  -7,  -8,
                  -9, -10, -11, -12, -13, -14, -15, -16};
  double b[16] = {2, 0, 1, 2, 1, 2, 1, 0, 0, 1, 2, 1, 2, 1, 0, 2};
  double expected[16] = {-12, -11, -9,  -13, -32, -27, -25, -33,
                         -52, -43, -41, -53, -72, -59, -57, -73};
  double c[16];

  strassen(a, b, c, 4);

  for (int i = 0; i < 16; i++) {
    EXPECT_EQ(c[i], expected[i]);
  }
}

TEST(Nikitin_test, OneRowOneColumn) {
  double a[1] = {2};
  double b[1] = {3};
  double expected[1] = {6};
  double c[1];

  strassen(a, b, c, 1);

  EXPECT_EQ(c[0], expected[0]);
}

TEST(Nikitin_test, ZeroMatrix) {
  double a[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  double b[16] = {2, 0, 1, 2, 1, 2, 1, 0, 0, 1, 2, 1, 2, 1, 0, 2};
  double expected[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  double c[16];

  strassen(a, b, c, 4);

  for (int i = 0; i < 16; i++) {
    EXPECT_EQ(c[i], expected[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
