// Copyright 2023 Korobeynikova Alice
#include "../../../modules/task_4/korobeynikova_a_histogram_linear_stretching/histogram_linear_stretching.h"

#include <iostream>

#include "../../../3rdparty/unapproved/unapproved.h"

Color RANGEMIN = static_cast<Color>(0);
Color RANGEMAX = static_cast<Color>(255);

using IntVector = std::vector<int>;

IntVector taskDistrib(const int thread_num, const int task_num) {
  IntVector task_per_proc(thread_num);
  int remained_rows = task_num % thread_num;
  for (int thread = 0; thread < thread_num; ++thread) {
    task_per_proc.at(thread) = task_num / thread_num + (remained_rows > 0);
    --remained_rows;
  }
  return task_per_proc;
}

static std::pair<Color, Color> findRange(const Color* image, const int size) {
  auto range = std::make_pair(RANGEMAX, RANGEMIN);
  for (int i = 0; i < size; ++i) {
    range.first = std::min(image[i], range.first);
    range.second = std::max(image[i], range.second);
  }
  return range;
}

static std::pair<Color, Color> findRangeParallel(const Color* image,
                                                 const int size) {
  auto thread_num = std::thread::hardware_concurrency();
  auto task_distrib = taskDistrib(thread_num, size);
  std::pair<Color, Color> range = {RANGEMAX, RANGEMIN};
  std::vector<std::thread> threads;
  std::vector<std::pair<Color, Color>> results(thread_num,
                                               {RANGEMAX, RANGEMIN});

  int elems_to_skip = task_distrib.at(0);
  for (int thread = 1; thread < thread_num && task_distrib.at(thread) != 0;
       ++thread) {
    threads.emplace_back(
        [&results, thread](const Color* image, const int size) {
          results[thread] = findRange(image, size);
        },
        image + elems_to_skip, task_distrib.at(thread));
    elems_to_skip += task_distrib.at(thread);
  }

  results[0] = findRange(image, task_distrib.at(0));

  for (auto& thread : threads) {
    thread.join();
  }

  for (int i = 1; i < results.size(); ++i) {
    results[0].first = std::min(results[i].first, results[0].first);
    results[0].second = std::max(results[i].second, results[0].second);
  }
  return results[0];
}

void linearHistogramStretchingImpl(Color* image, const int size,
                                   std::pair<Color, Color> range) {
  if (range.second != range.first) {
    for (int i = 0; i < size; ++i) {
      image[i] = (image[i] - range.first) * (RANGEMAX - RANGEMIN) /
                 (range.second - range.first);
    }
  }
}

void linearHistogramStretching(Color* image, const int size) {
  std::pair<Color, Color> range = findRange(image, size);

  linearHistogramStretchingImpl(image, size, range);
}

void linearHistogramStretchingParallel(Color* image, const int size) {
  auto thread_num = std::thread::hardware_concurrency();
  std::pair<Color, Color> range = findRangeParallel(image, size);
  if (range.second != range.first) {
    auto task_distrib = taskDistrib(thread_num, size);
    std::vector<std::thread> threads;
    std::vector<std::pair<Color, Color>> results(thread_num);

    int elems_to_skip = task_distrib.at(0);
    for (int thread = 1; thread < thread_num; ++thread) {
      if (task_distrib.at(thread) != 0) {
        threads.emplace_back(linearHistogramStretchingImpl,
                             &image[elems_to_skip], task_distrib.at(thread),
                             range);
      }
      elems_to_skip += task_distrib.at(thread);
    }
    linearHistogramStretchingImpl(image, task_distrib.at(0), range);
    for (auto& thread : threads) {
      thread.join();
    }
  }
}
