// Copyright 2023 Tsvetkov Maxim
#include "../../../modules/task_2/tsvetkov_m_radix_batcher/radix_batcher.h"
#include <omp.h>
#include <algorithm>
#include <cstdint>
#include <cstring>
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

void radixSortIntegers(int *array, int size) {
  std::vector<int> negativePart, nonNegativePart;
  for (int i = 0; i < size; i++) {
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
  std::memcpy(array, sortedData.data(), size * sizeof(int));
}

void BatcherOddEvenMerge(int *partStartPtr, int batchSize, bool isOdd) {
  std::vector<int> tmp;
  tmp.reserve(batchSize);

  int i = 0, j = batchSize;
  int border1 = batchSize - 2, border2 = (batchSize * 2) - 2;
  if (isOdd) {
    ++i, ++j;
    ++border1, ++border2;
  }

  while (i <= border1 && j <= border2) {
    if (partStartPtr[i] <= partStartPtr[j]) {
      tmp.push_back(partStartPtr[i]);
      i += 2;
    } else {
      tmp.push_back(partStartPtr[j]);
      j += 2;
    }
  }

  while (i <= border1) {
    tmp.push_back(partStartPtr[i]);
    i += 2;
  }
  while (j <= border2) {
    tmp.push_back(partStartPtr[j]);
    j += 2;
  }

  int k = 0;
  if (isOdd)
    ++k;

  for (int t = 0; t != tmp.size(); k += 2, ++t)
    partStartPtr[k] = tmp[t];
}

void ParallelBatcherOddEvenMerge(int *vec, int batchSize, int batchCount) {
#pragma omp parallel for
  for (int i = 0; i < batchCount; ++i) {
    int j = (i % 2 == 0) ? i / 2 : (i - 1) / 2;
    int *partStartPtr = vec + (batchSize * 2) * j;
    BatcherOddEvenMerge(partStartPtr, batchSize, i % 2 == 1);
  }

#pragma omp parallel for
  for (int i = 0; i < batchCount; i += 2) {
    int j = (i % 2 == 0) ? i / 2 : (i - 1) / 2;
    int *partStartPtr = vec + (batchSize * 2) * j;
    for (int k = 1; k <= (batchSize * 2) - 3; ++k) {
      if (partStartPtr[k + 1] < partStartPtr[k]) {
        std::swap(partStartPtr[k + 1], partStartPtr[k]);
      }
    }
  }
}

void radixSortIntegersWithBatcherMerge(std::vector<int> *data) {
  int oldSize = data->size();
  int batchSize = 256;

  if (data->size() <= batchSize) {
    radixSortIntegers(data->data(), data->size());
    return;
  }

  while (data->size() > 0 && (data->size() & (data->size() - 1))) {
    data->push_back(INT32_MAX);
  }

  int *array = data->data();
  int batchCount = data->size() / batchSize;

#pragma omp parallel for
  for (int i = 0; i < batchCount; ++i) {
    int *partStartPtr = array + i * batchSize;
    radixSortIntegers(partStartPtr, batchSize);
  }

  while (data->size() / batchSize != 1) {
    ParallelBatcherOddEvenMerge(array, batchSize, batchCount);
    batchCount /= 2, batchSize *= 2;
  }
  data->resize(oldSize);
}
