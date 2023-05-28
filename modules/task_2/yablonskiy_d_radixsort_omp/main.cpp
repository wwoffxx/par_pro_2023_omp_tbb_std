// Copyright 2023 Yablonskiy Dmitriy
#include <gtest/gtest.h>
#include "./radixsort.h"

TEST(RadixSort_OMP, TEST_arr_size_0) {
  std::vector<int> arr = {};
  ASSERT_ANY_THROW(radixSort_mer(&arr));
}

TEST(RadixSort_OMP, TEST_already_sorted_arr) {
  std::vector<int> arr_s = create_rand_arr(10);
  std::sort(arr_s.begin(), arr_s.end());

  std::vector<int> arr = radixSort_mer(&arr_s);

  ASSERT_EQ(arr, arr_s);
}

TEST(RadixSort_OMP, TEST_arr_size_10) {
  const int SIze = 10;
  std::vector<int> arr_1 = create_rand_arr(SIze);

  std::vector<int> arr_2 = radixSort_mer(&arr_1);
  std::sort(arr_1.begin(), arr_1.end());

  ASSERT_EQ(arr_1, arr_2);
}

TEST(RadixSort_OMP, TEST_arr_size_1000) {
  const int SIze = 1000;
  std::vector<int> arr_1 = create_rand_arr(SIze);

  std::vector<int> arr_2 = radixSort_mer(&arr_1);
  std::sort(arr_1.begin(), arr_1.end());

  ASSERT_EQ(arr_1, arr_2);
}

TEST(RadixSort_OMP, TEST_arr_size_100000) {
  const int SIze = 100000;
  std::vector<int> arr_1 = create_rand_arr(SIze);

  std::vector<int> arr_2 = radixSort_mer(&arr_1);
  std::sort(arr_1.begin(), arr_1.end());

  ASSERT_EQ(arr_1, arr_2);
}
