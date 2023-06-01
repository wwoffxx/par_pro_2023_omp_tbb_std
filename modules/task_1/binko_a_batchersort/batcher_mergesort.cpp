// Copyright 2023 Binko Alexandr
#include "../../../modules/task_1/binko_a_batchersort/batcher_mergesort.h"

#include <algorithm>
#include <random>
#include <vector>

using vector_d = std::vector<double>;
constexpr size_t bv = 256;

vector_d getRandVec(size_t vec_size, double lower_bound, double upper_bound) {
  vector_d vec(vec_size);
  std::uniform_real_distribution<double> distribution(lower_bound, upper_bound);
  std::random_device device;
  std::mt19937 rnd(device());

  for (size_t i = 0; i < vec_size; ++i) vec[i] = distribution(rnd);

  return vec;
}

std::vector<vector_d> genDigitCounters(vector_d* source_vec, size_t elem_num) {
  std::vector<vector_d> digitCounters(256);
  int index_sv = 0;
  int curr_byte = 0;

  for (size_t byte_num = 0; byte_num < sizeof(double); ++byte_num) {
    for (size_t elem_ind = 0; elem_ind < elem_num; ++elem_ind) {
      curr_byte = static_cast<int>(
          *((unsigned char*)&(*source_vec)[elem_ind] + byte_num));
      digitCounters[curr_byte].push_back((*source_vec)[elem_ind]);
    }

    size_t count_size = 0;
    for (size_t i = 0; i < bv; ++i) {
      if (!digitCounters.empty()) {
        count_size = digitCounters[i].size();
        for (size_t j = 0; j < count_size; ++j) {
          (*source_vec)[index_sv++] = digitCounters[i][j];
        }
        digitCounters[i].clear();
      }
    }
    index_sv = 0;
  }

  return digitCounters;
}

void radixPass(vector_d* source_vec,
               const std::vector<vector_d>& digitCounters) {
  size_t index_v = 0;
  size_t count_size = 0;

  for (size_t i = bv - 1; i >= bv / 2; --i) {
    if (!digitCounters[i].empty()) {
      count_size = digitCounters[i].size();
      for (size_t k = count_size - 1; k >= 1; --k) {
        (*source_vec)[index_v++] = digitCounters[i][k];
      }
      (*source_vec)[index_v++] = digitCounters[i][0];
    }
  }

  for (size_t i = 0; i < bv / 2; ++i) {
    if (!digitCounters[i].empty()) {
      count_size = digitCounters[i].size();
      for (size_t j = 0; j < count_size; ++j) {
        (*source_vec)[index_v++] = digitCounters[i][j];
      }
    }
  }
}

void floatRadixSort(vector_d* source_vec) {
  size_t elem_num = source_vec->size();

  auto digitCounters = genDigitCounters(source_vec, elem_num);

  int count_index = 0;
  for (size_t i = 0; i < elem_num; ++i) {
    count_index = static_cast<int>(*((unsigned char*)&(*source_vec)[i] + 7));
    digitCounters[count_index].push_back((*source_vec)[i]);
  }

  radixPass(source_vec, digitCounters);
}

void evenSplitter(vector_d* res_vec, const vector_d& first_vec,
                  const vector_d& second_vec) {
  size_t index_a = 0;
  size_t index_b = 0;  // plus
  size_t i = 0;

  auto first_size = first_vec.size();
  auto second_size = second_vec.size();

  while ((index_a < first_size) && (index_b < second_size)) {
    if (first_vec[index_a] <= second_vec[index_b]) {
      (*res_vec)[i] = first_vec[index_a];
      index_a += 2;
    } else {
      (*res_vec)[i] = second_vec[index_b];
      index_b += 2;
    }
    i += 2;
  }

  if (index_a >= first_size) {  // _
    for (size_t j = index_b; j < second_size && i < first_size + second_size;
         j += 2, i += 2)
      (*res_vec)[i] = second_vec[j];
  } else {
    for (size_t j = index_a; j < first_size && i < first_size + second_size;
         j += 2, i += 2)
      (*res_vec)[i] = first_vec[j];
  }
}

void oddSplitter(vector_d* res_vec, const vector_d& first_vec,
                 const vector_d& second_vec) {
  size_t index_a = 1;
  size_t index_b = 1;
  size_t i = 1;

  auto first_size = first_vec.size();
  auto second_size = second_vec.size();

  while ((index_a < first_size) && (index_b < second_size)) {
    if (first_vec[index_a] <= second_vec[index_b]) {
      (*res_vec)[i] = first_vec[index_a];
      index_a += 2;
    } else {
      (*res_vec)[i] = second_vec[index_b];
      index_b += 2;
    }
    i += 2;
  }

  if (index_a >= first_size) {
    for (size_t j = index_b; j < second_size && i < first_size + second_size;
         j += 2, i += 2)
      (*res_vec)[i] = second_vec[j];
  } else {
    for (size_t j = index_a; j < first_size && i < first_size + second_size;
         j += 2, i += 2)
      (*res_vec)[i] = first_vec[j];
  }

  if (first_size % 2 == 1 && second_size % 2 == 1) {
    (*res_vec)[first_size + second_size - 1] =
        std::max(first_vec[first_size - 1], second_vec[second_size - 1]);
  }
}

void batcherComparator(vector_d* res_vec) {
  auto res_size = res_vec->size();

  for (size_t i = 1; i < res_size; ++i) {
    if ((*res_vec)[i] < (*res_vec)[i - 1])
      std::swap((*res_vec)[i], (*res_vec)[i - 1]);
  }
}

vector_d batcherMerge(const vector_d& first_vec, const vector_d& second_vec) {
  auto first_size = first_vec.size();
  auto second_size = second_vec.size();
  vector_d res_vec(first_size + second_size);

  evenSplitter(&res_vec, first_vec, second_vec);
  oddSplitter(&res_vec, first_vec, second_vec);
  batcherComparator(&res_vec);

  return res_vec;
}
