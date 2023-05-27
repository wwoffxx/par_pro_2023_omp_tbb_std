// Copyright 2023 Sharovatov Daniil
#include "../../../modules/task_3/sharovatov_d_int_radix_merge/int_radix_merge.h"

int getMax(std::vector<int>* vec) {
  std::vector<int>& arr = *vec;
  int maxNum = arr[0];
  for (int i = 1; i < arr.size(); i++) {
    if (arr[i] > maxNum) {
      maxNum = arr[i];
    }
  }
  return maxNum;
}

void radixSortForExp(std::vector<int>* vec, int exp) {
  std::vector<int>& arr = *vec;
  int n = arr.size();
  std::vector<int> output(n);
  std::vector<int> count(10, 0);

  for (int i = 0; i < n; i++) {
    count[(arr[i] / exp) % 10]++;
  }

  for (int i = 1; i < 10; i++) {
    count[i] += count[i - 1];
  }

  for (int i = n - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  for (int i = 0; i < n; i++) {
    arr[i] = output[i];
  }
}

void radixSort(std::vector<int>* vec) {
  int maxNum = getMax(vec);

  for (int exp = 1; maxNum / exp > 0; exp *= 10) {
    radixSortForExp(vec, exp);
  }
}

std::vector<int> radixMerge(const std::vector<int>& firstVec, const std::vector<int>& secondVec) {
  std::vector<int> temp(firstVec.size() + secondVec.size());
  std::merge(firstVec.begin(), firstVec.end(), secondVec.begin(),
             secondVec.end(), temp.begin());
  return temp;
}

class radixSorting {
 public:
  mutable std::vector<int> result;
  radixSorting() = default;
  radixSorting(const radixSorting& o, tbb::split) {}

  void operator()(const tbb::blocked_range<std::vector<int>::iterator>& r) {
    std::copy(r.begin(), r.end(), std::back_inserter(result));
    radixSort(&result);
  }

  void join(const radixSorting& rhs) {
    result = radixMerge(rhs.result, result);
  }
};

std::vector<int> radixSortMerge(std::vector<int>* vec) {
  const int vectorSize = (*vec).size();
  if (vectorSize == 0) throw -1;

  std::vector<int> temp(*vec);
  radixSorting sorting;

  tbb::parallel_reduce(
      tbb::blocked_range<std::vector<int>::iterator>(temp.begin(), temp.end()),
                       sorting);

  return sorting.result;
}

std::vector<int> getRandomVector(int size) {
  if (size <= 0) {
    throw(-1);
  }

  std::vector<int> randomVector(size);

  std::random_device dev;
  std::mt19937 gen(dev());

  for (int i = 0; i < size; i++) {
    randomVector[i] = gen() % 1000;
  }

  return randomVector;
}
