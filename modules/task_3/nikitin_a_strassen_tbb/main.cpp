// Copyright 2023 Nikitin Aleksandr
#include <gtest/gtest.h>

#include <vector>

#include "./strassen_tbb.h"

TEST(Nikitin_test, NaiveMultiplication) {
  double a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double b[16] = {2, 0, 1, 2, 1, 2, 1, 0, 0, 1, 2, 1, 2, 1, 0, 2};

  double expected[16] = {10, 5,  6,  10, 26, 13, 18, 26,
                         42, 21, 30, 42, 58, 29, 42, 58};

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

  double expected[16] = {10, 5,  6,  10, 26, 13, 18, 26,
                         42, 21, 30, 42, 58, 29, 42, 58};

  double c[16];

  int size = 4;

  strassen(a, b, c, size);

  for (int i = 0; i < size * size; i++) {
    EXPECT_EQ(c[i], expected[i]);
  }
}

TEST(Nikitin_test, NonPowerOf2Size) {
  double a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double b[16] = {2, 0, 1, 2, 1, 2, 1, 0, 0, 1, 2, 1, 2, 1, 0, 2};

  double expected[16] = {10, 5,  6,  10, 26, 13, 18, 26,
                         42, 21, 30, 42, 58, 29, 42, 58};

  double c[16];

  int size = 4;

  size = 3;

  double expectedNonPowerOf2[9] = {5, 5, 5, 11, 11, 11, 17, 17, 17};

  strassen(a, b, c, size);

  for (int i = 0; i < size * size; i++) {
    EXPECT_EQ(c[i], expectedNonPowerOf2[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
