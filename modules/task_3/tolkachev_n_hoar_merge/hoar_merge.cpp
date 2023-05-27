// Copyright 2023 Tolkachev
#include "../../../modules/task_3/tolkachev_n_hoar_merge/hoar_merge.h"

std::vector<int> Getvec(int n) {
  std::random_device randomDevice;
  std::mt19937 engine(randomDevice());
  std::uniform_int_distribution<> dist(0, 100);
  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    vec[i] = dist(engine);
  }
  return vec;
}
void HoarSort(std::vector<int>* arr, int first, int last) {
  std::vector<int>& s = *arr;
  int left = first;
  int right = last;
  int middle = s[(first + last) / 2];

  do {
    while (s[left] < middle) left++;
    while (s[right] > middle) right--;

    if (left <= right) {
      if (s[left] > s[right]) {
        std::swap(s[left], s[right]);
      }
      left++;
      right--;
    }
  } while (left <= right);

  if (left < last) HoarSort(&s, left, last);
  if (first < right) HoarSort(&s, first, right);
}
std::vector<int> Merge(std::vector<int>* arr, std::vector<int>* arr2) {
  std::vector<int>& s1 = *arr;
  std::vector<int>& s2 = *arr2;
  std::vector<int> result(s1.size() + s2.size());
  std::merge(s1.begin(), s1.end(), s2.begin(), s2.end(), result.begin());
  return result;
}
std::vector<int> SortParallel(std::vector<int>* vec) {
    std::vector<int> res;
    tbb::spin_mutex mutex;
    tbb::parallel_for(tbb::blocked_range<std::vector<int>::iterator>(
    vec->begin(), vec->end(), 3),
    [&](tbb::blocked_range<std::vector<int>::iterator>range) {
    std::vector<int>local_vec =
    std::vector<int>(range.begin(), range.end());
    HoarSort(&local_vec, 0, local_vec.size() - 1);
    mutex.lock();
    res = Merge(&res, &local_vec);
    mutex.unlock();
    });
  return res;
  }
