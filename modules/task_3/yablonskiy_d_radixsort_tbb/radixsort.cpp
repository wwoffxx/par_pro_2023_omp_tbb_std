// Copyright 2023 Yablonskiy Dmitriy
#include "../../../modules/task_3/yablonskiy_d_radixsort_tbb/radixsort.h"

std::vector<int> create_rand_arr(int size) {
  if (size <= 0)
    throw "error";

  std::vector<int> rand_arr(size);

  std::random_device dev;
  std::mt19937 gen(dev());

  for (int i = 0; i < size; i++)
    rand_arr[i] = gen() % 1000;

  return rand_arr;
}

int max_elem(std::vector<int> *arr) {
  std::vector<int> &mass = *arr;
  int maximum = mass[0];
  for (int i = 1; i < mass.size(); i++) {
    if (mass[i] > maximum)
      maximum = mass[i];
  }
  return maximum;
}

void radix_sort_e(std::vector<int> *arr, int exp) {
  std::vector<int> &mass = *arr;
  int size = mass.size();
  std::vector<int> o(size);
  std::vector<int> c(10, 0);

  for (int i = 0; i < size; i++)
    c[(mass[i] / exp) % 10] += 1;

  for (int i = 1; i < 10; i++)
    c[i] += c[i - 1];

  for (int i = size - 1; i >= 0; i--) {
    int tmp = c[(mass[i] / exp) % 10];
    o[tmp - 1] = mass[i];
    c[(mass[i] / exp) % 10] -= 1;
  }

  for (int i = 0; i < size; i++)
    mass[i] = o[i];
}

void radix_sort(std::vector<int> *arr) {
  int maximum = max_elem(arr);

  for (int exp = 1; maximum / exp > 0; exp *= 10)
    radix_sort_e(arr, exp);
}

std::vector<int> radix_m(const std::vector<int> &arr_1,
                         const std::vector<int> &arr_2) {
  std::vector<int> t(arr_1.size() + arr_2.size());
  std::merge(arr_1.begin(), arr_1.end(), arr_2.begin(), arr_2.end(), t.begin());
  return t;
}

class r_sort {
 public:
  mutable std::vector<int> res;
  r_sort() = default;
  r_sort(const r_sort &o, tbb::split) {}

  void operator()(const tbb::blocked_range<std::vector<int>::iterator> &r) {
    std::copy(r.begin(), r.end(), std::back_inserter(res));
    radix_sort(&res);
  }

  void join(const r_sort &rhs){
    res = radix_m(rhs.res, res);
  }
};

std::vector<int> radix_sort_mer(std::vector<int> *arr) {
  const int arr_size = (*arr).size();
  if (arr_size == 0)
    throw "error";

  std::vector<int> t(*arr);
  r_sort sorting;

  tbb::parallel_reduce(
      tbb::blocked_range<std::vector<int>::iterator>(t.begin(), t.end()),
      sorting);
  return sorting.res;
}
