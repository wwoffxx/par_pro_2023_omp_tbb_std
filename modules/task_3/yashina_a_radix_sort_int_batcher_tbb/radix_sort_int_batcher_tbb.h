// Copyright 2023 Yashina Anastasia
#ifndef MODULES_TASK_3_YASHINA_A_RADIX_SORT_INT_BATCHER_TBB_RADIX_SORT_INT_BATCHER_TBB_H_
#define MODULES_TASK_3_YASHINA_A_RADIX_SORT_INT_BATCHER_TBB_RADIX_SORT_INT_BATCHER_TBB_H_
#include <vector>

bool checkSort(std::vector<int> arr);
void radixSort(std::vector<int> *vec);
void countSort(std::vector<int> *vec, int exp);
int getMax(std::vector<int> *vec);
std::vector<int> EvenOddBatch(std::vector<int> vec1, std::vector<int> vec2);
std::vector<int> evenBatch(std::vector<int> vec1, std::vector<int> vec2);
std::vector<int> oddBatch(std::vector<int> vec1, std::vector<int> vec2);
std::vector<int> GetRandVector(int size);

#endif  // MODULES_TASK_3_YASHINA_A_RADIX_SORT_INT_BATCHER_TBB_RADIX_SORT_INT_BATCHER_TBB_H_
