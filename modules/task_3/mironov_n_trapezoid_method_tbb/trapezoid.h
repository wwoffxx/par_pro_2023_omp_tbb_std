// Copyright 2023 Mironov Nikita
#ifndef MODULES_TASK_3_MIRONOV_N_TRAPEZOID_METHOD_TBB_TRAPEZOID_H_
#define MODULES_TASK_3_MIRONOV_N_TRAPEZOID_METHOD_TBB_TRAPEZOID_H_

#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>
#include <time.h>
#include <functional>
#include <vector>
#include <utility>
#include <iostream>
#include <cmath>

double trapezoid_method(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int dimensions,
    int N);

#endif  // MODULES_TASK_3_MIRONOV_N_TRAPEZOID_METHOD_TBB_TRAPEZOID_H_
