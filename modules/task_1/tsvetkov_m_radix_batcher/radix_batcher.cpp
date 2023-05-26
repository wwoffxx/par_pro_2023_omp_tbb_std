// Copyright 2023 Tsvetkov Maxim
#include "../../../modules/task_1/tsvetkov_m_radix_batcher/radix_batcher.h"
#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>
#include <utility>
#include <vector>

int getDigit(int num, int digit) {
  int divider = 1;
  for (int i = 0; i < digit; ++i)
    divider *= 10;
  return (num / divider) % 10;
}

void radixSort(std::vector<int> *data) {
  auto &arr = *data;
  int maxNum = *std::max_element(arr.begin(), arr.end());
  int numDigits = std::to_string(maxNum).length();

  std::vector<std::vector<int>> buckets(10);

  for (int digit = 0; digit < numDigits; ++digit) {
    for (int i = 0; i < arr.size(); ++i) {
      int currentDigit = getDigit(arr[i], digit);
      buckets[currentDigit].push_back(arr[i]);
    }

    int index = 0;
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < buckets[i].size(); ++j) {
        arr[index++] = buckets[i][j];
      }
      buckets[i].clear();
    }
  }
}

std::vector<int> radixSortIntegers(const std::vector<int> &array) {
  std::vector<int> negativePart, nonNegativePart;
  for (int i = 0; i < array.size(); i++) {
    if (array[i] >= 0) {
      nonNegativePart.push_back(array[i]);
    } else {
      negativePart.push_back(-array[i]);
    }
  }
  if (!negativePart.empty())
    radixSort(&negativePart);
  if (!nonNegativePart.empty())
    radixSort(&nonNegativePart);

  std::for_each(negativePart.begin(), negativePart.end(),
                [](auto &val) { val = -val; });
  std::reverse(negativePart.begin(), negativePart.end());
  std::vector<int> sortedData(std::move(negativePart));
  sortedData.insert(sortedData.end(), nonNegativePart.begin(),
                    nonNegativePart.end());
  return sortedData;
}
