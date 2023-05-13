// Copyright 2023 Yablonskiy Dmitriy
#include "../../../modules/task_2/yablonskiy_d_radixsort_omp/radixsort.h"

int max_elem(std::vector<int> *arr) {
  std::vector<int> &arr_tmp = *arr;
  int max_e = arr_tmp[0];
  for (int i = 1; i < arr_tmp.size(); i++) {
    if (arr_tmp[i] > max_e)
      max_e = arr_tmp[i];
  }
  return max_e;
}

void radixSort_e(std::vector<int> *arr, int exp) {
  std::vector<int> &arr_tmp = *arr;
  int n = arr_tmp.size();
  std::vector<int> result(n);
  std::vector<int> count(10, 0);

  for (int i = 0; i < n; i++)
    count[(arr_tmp[i] / exp) % 10]++;

  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (int i = n - 1; i >= 0; i--) {
    result[count[(arr_tmp[i] / exp) % 10] - 1] = arr_tmp[i];
    count[(arr_tmp[i] / exp) % 10]--;
  }

  for (int i = 0; i < n; i++)
    arr_tmp[i] = result[i];
}

void radixSort(std::vector<int> *arr) {
  int max_e = max_elem(arr);

  for (int exp = 1; max_e / exp > 0; exp *= 10)
    radixSort_e(arr, exp);
}

std::vector<int> merge(std::vector<int> *arr_1, std::vector<int> *arr_2) {
  std::vector<int> temp(arr_1->size() + arr_2->size());
  std::merge((*arr_1).begin(), (*arr_1).end(), (*arr_2).begin(), (*arr_2).end(),
             temp.begin());
  return temp;
}

std::vector<int> radixSort_mer(std::vector<int> *arr) {
  const int vectorSize = (*arr).size();
  if (vectorSize == 0)
    throw -1;

  std::vector<int> result;

#pragma omp parallel
  {
    int thread = omp_get_thread_num();
    int threadNum = omp_get_num_threads();

    int vecSize = arr->size();
    int step = vecSize / threadNum;
    int leftOffset = step * thread;
    int rightOffset = step * (thread + 1);
    if ((vecSize / threadNum != 0) && (thread == threadNum - 1)) {
      rightOffset += vecSize - step * threadNum;
    }
    std::vector<int> arr_tmp((*arr).begin() + leftOffset,
                             (*arr).begin() + rightOffset);

    radixSort(&arr_tmp);

#pragma omp critical
    { result = merge(&result, &arr_tmp); }
  }

  return result;
}

std::vector<int> create_rand_arr(int size) {
  if (size <= 0)
    throw(-1);

  std::vector<int> rand_arr(size);

  std::random_device dev;
  std::mt19937 gen(dev());

  for (int i = 0; i < size; i++)
    rand_arr[i] = gen() % 1000;

  return rand_arr;
}
