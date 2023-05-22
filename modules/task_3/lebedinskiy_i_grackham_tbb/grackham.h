// Copyright 2023 Lebedinskiy Ilya
#ifndef MODULES_TASK_3_LEBEDINSKIY_I_GRACKHAM_TBB_GRACKHAM_H_
#define MODULES_TASK_3_LEBEDINSKIY_I_GRACKHAM_TBB_GRACKHAM_H_

#include <tbb/tbb.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

double distance(const std::pair<double, double>& dot1,
    const std::pair<double, double>& dot2);
int rotation(const std::pair<double, double>& dot1,
    const std::pair<double, double>& dot2, const std::pair<double, double>& dot3);
std::vector<std::pair<double, double>> grackham_seq(
    std::vector<std::pair<double, double>>::iterator beg,
    std::vector<std::pair<double, double>>::iterator end);
std::vector<std::pair<double, double>> gen_dots(int vectorSize);
std::vector<std::pair<double, double>> grackham_tbb(
    std::vector<std::pair<double, double>>::iterator beg,
    std::vector<std::pair<double, double>>::iterator end,
    std::size_t n_threads);

#endif  // MODULES_TASK_3_LEBEDINSKIY_I_GRACKHAM_TBB_GRACKHAM_H_
