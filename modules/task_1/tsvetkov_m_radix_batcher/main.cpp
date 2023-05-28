// Copyright 2023 Tsvetkov Maxim
#include <gtest/gtest.h>
#include <algorithm>
#include <random>
#include "../../../modules/task_1/tsvetkov_m_radix_batcher/radix_batcher.h"


TEST(radix_seq, test_1) {
  std::vector<int> arr1 = {9, 8, 7, 6, 5, -1, -2};
  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  std::vector<int> res = radixSortIntegers(arr1);
  ASSERT_EQ(arr2.size(), res.size());
  for (int i = 0; i < res.size(); i++) {
    ASSERT_EQ(arr2[i], res[i]);
  }
}

TEST(radix_seq, test_2) {
  std::vector<int> arr1 = {4, 3, 2, 1};
  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  std::vector<int> res = radixSortIntegers(arr1);
  ASSERT_EQ(arr2.size(), res.size());
  for (int i = 0; i < res.size(); i++) {
    ASSERT_EQ(arr2[i], res[i]);
  }
}

TEST(radix_seq, test_3) {
  std::vector<int> arr1 = {100, 200, 300, 400, 500};
  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  std::vector<int> res = radixSortIntegers(arr1);
  ASSERT_EQ(arr2.size(), res.size());
  for (int i = 0; i < res.size(); i++) {
    ASSERT_EQ(arr2[i], res[i]);
  }
}

TEST(radix_seq, test_4) {
  std::vector<int> arr1 = {-10, 0, 10, -20, 20};
  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  std::vector<int> res = radixSortIntegers(arr1);
  ASSERT_EQ(arr2.size(), res.size());
  for (int i = 0; i < res.size(); i++) {
    ASSERT_EQ(arr2[i], res[i]);
  }
}

TEST(radix_seq, test_5) {
  std::vector<int> arr1 = {1, 3, 5, 7, 9};
  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  std::vector<int> res = radixSortIntegers(arr1);
  ASSERT_EQ(arr2.size(), res.size());
  for (int i = 0; i < res.size(); i++) {
    ASSERT_EQ(arr2[i], res[i]);
  }
}

TEST(radix_seq, test_6) {
  std::vector<int> arr1 = {0, 0, 0, 0, 0};
  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  std::vector<int> res = radixSortIntegers(arr1);
  ASSERT_EQ(arr2.size(), res.size());
  for (int i = 0; i < res.size(); i++) {
    ASSERT_EQ(arr2[i], res[i]);
  }
}

TEST(radix_seq, test_7) {
  std::vector<int> arr1 = {-5, -4, -3, -2, -1};
  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  std::vector<int> res = radixSortIntegers(arr1);
  ASSERT_EQ(arr2.size(), res.size());
  for (int i = 0; i < res.size(); i++) {
    ASSERT_EQ(arr2[i], res[i]);
  }
}

TEST(radix_seq, test_8) {
  std::vector<int> arr1 = {5, 4, 3, 2, 1};
  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  std::vector<int> res = radixSortIntegers(arr1);
  ASSERT_EQ(arr2.size(), res.size());
  for (int i = 0; i < res.size(); i++) {
    ASSERT_EQ(arr2[i], res[i]);
  }
}

TEST(radix_seq, test_9) {
  std::vector<int> arr1 = {-1, 0, 1};
  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  std::vector<int> res = radixSortIntegers(arr1);
  ASSERT_EQ(arr2.size(), res.size());
  for (int i = 0; i < res.size(); i++) {
    ASSERT_EQ(arr2[i], res[i]);
  }
}

TEST(radix_seq, random_test) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-1000, 1000);

  const int arr_size = 1000;
  std::vector<int> arr1(arr_size);
  for (int i = 0; i < arr_size; ++i) {
    arr1[i] = dist(gen);
  }

  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  std::vector<int> res = radixSortIntegers(arr1);

  ASSERT_EQ(arr2.size(), res.size());
  for (int i = 0; i < res.size(); i++) {
    ASSERT_EQ(arr2[i], res[i]);
  }
}
