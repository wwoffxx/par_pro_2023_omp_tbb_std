// Copyright 2023 Tsvetkov Maxim
#include <gtest/gtest.h>
#include <algorithm>
#include <random>
#include "../../../modules/task_3/tsvetkov_m_radix_batcher/radix_batcher.h"

TEST(radix_omp, test_0) {
  std::vector<int> arr1 = {};
  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  radixSortIntegersWithBatcherMerge(arr1.begin(), arr1.end());
  ASSERT_EQ(arr2.size(), arr1.size());
  for (int i = 0; i < arr1.size(); i++) {
    ASSERT_EQ(arr2[i], arr1[i]);
  }
}

TEST(radix_omp, test_1) {
  std::vector<int> arr1 = {9, 8, 7, 6, 5, -1, -2};
  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  radixSortIntegersWithBatcherMerge(arr1.begin(), arr1.end());
  ASSERT_EQ(arr2.size(), arr1.size());
  for (int i = 0; i < arr1.size(); i++) {
    ASSERT_EQ(arr2[i], arr1[i]);
  }
}

TEST(radix_omp, random_test_100) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-1000, 1000);

  const int arr_size = 100;
  std::vector<int> arr1(arr_size);
  for (int i = 0; i < arr_size; ++i) {
    arr1[i] = dist(gen);
  }

  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  radixSortIntegersWithBatcherMerge(arr1.begin(), arr1.end());

  ASSERT_EQ(arr2.size(), arr1.size());
  for (int i = 0; i < arr1.size(); i++) {
    ASSERT_EQ(arr2[i], arr1[i]);
  }
}

TEST(radix_omp, random_test_500) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-1000, 1000);

  const int arr_size = 500;
  std::vector<int> arr1(arr_size);
  for (int i = 0; i < arr_size; ++i) {
    arr1[i] = dist(gen);
  }

  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  radixSortIntegersWithBatcherMerge(arr1.begin(), arr1.end());

  ASSERT_EQ(arr2.size(), arr1.size());
  for (int i = 0; i < arr1.size(); i++) {
    ASSERT_EQ(arr2[i], arr1[i]);
  }
}

TEST(radix_omp, random_test_1000) {
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
  radixSortIntegersWithBatcherMerge(arr1.begin(), arr1.end());

  ASSERT_EQ(arr2.size(), arr1.size());
  for (int i = 0; i < arr1.size(); i++) {
    ASSERT_EQ(arr2[i], arr1[i]);
  }
}

TEST(radix_omp, random_test_5000) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-1000, 1000);

  const int arr_size = 5000;
  std::vector<int> arr1(arr_size);
  for (int i = 0; i < arr_size; ++i) {
    arr1[i] = dist(gen);
  }

  std::vector<int> arr2 = arr1;
  std::sort(arr2.begin(), arr2.end());
  radixSortIntegersWithBatcherMerge(arr1.begin(), arr1.end());

  ASSERT_EQ(arr2.size(), arr1.size());
  for (int i = 0; i < arr1.size(); i++) {
    ASSERT_EQ(arr2[i], arr1[i]);
  }
}
