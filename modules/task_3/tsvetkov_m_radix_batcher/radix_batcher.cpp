// Copyright 2023 Tsvetkov Maxim
#include "../../../modules/task_3/tsvetkov_m_radix_batcher/radix_batcher.h"
#include <tbb/tbb.h>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <functional>
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

void radixSortIntegers(std::vector<int>::iterator first,
                       std::vector<int>::iterator last) {
  std::vector<int> negativePart, nonNegativePart;
  for (auto i = first; i < last; i++) {
    if (*i >= 0) {
      nonNegativePart.push_back(*i);
    } else {
      negativePart.push_back(-*i);
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
  std::copy(sortedData.begin(), sortedData.end(), first);
}

void BatcherOddEvenMerge(std::vector<int>::iterator partStartPtr, int batchSize,
                         bool isOdd) {
  std::vector<int> tmp;
  tmp.reserve(batchSize);

  int i = 0, j = batchSize;
  int borderOdd = batchSize - 2, borderEven = (batchSize * 2) - 2;
  if (isOdd) {
    ++i, ++j;
    ++borderOdd, ++borderEven;
  }

  while (i <= borderOdd && j <= borderEven) {
    if (*(partStartPtr + i) <= *(partStartPtr + j)) {
      tmp.push_back(*(partStartPtr + i));
      i += 2;
    } else {
      tmp.push_back(*(partStartPtr + j));
      j += 2;
    }
  }

  while (i <= borderOdd) {
    tmp.push_back(*(partStartPtr + i));
    i += 2;
  }
  while (j <= borderEven) {
    tmp.push_back(*(partStartPtr + j));
    j += 2;
  }
}

void radixSortIntegersWithBatcherMerge(std::vector<int>::iterator first,
                                       std::vector<int>::iterator last) {
  using my_range = std::pair<std::size_t, std::size_t>;
  namespace ph = std::placeholders;
  auto BatcherMerge = std::bind(std::inplace_merge<std::vector<int>::iterator>,
                                ph::_1, ph::_2, ph::_3);
  tbb::parallel_deterministic_reduce(
      tbb::blocked_range<int>(0, last - first, 500), my_range(),
      [&](const tbb::blocked_range<int> &r, my_range v) -> my_range {
        v = std::make_pair(r.begin(), r.end());
        radixSortIntegers(first + v.first, first + v.second);
        return v;
      },
      [&](my_range v1, my_range v2) -> my_range {
        auto partStartPtr = first + v1.first;
        BatcherOddEvenMerge(first + v1.first, v2.second - v1.first,
                            v1.first % 2);
        BatcherMerge(first + v1.first, first + v1.second, first + v2.second);
        return {v1.first, v2.second};
      });
}
