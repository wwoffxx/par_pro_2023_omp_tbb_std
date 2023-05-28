// Copyright 2023 Krotov Aleksey
#ifndef MODULES_TASK_3_KROTOV_A_INTEGR_RECT_INTEGR_RECT_H_
#define MODULES_TASK_3_KROTOV_A_INTEGR_RECT_INTEGR_RECT_H_

#include <gtest/gtest.h>
#include <tbb/tbb.h>

#include <chrono>  // NOLINT [build/c++11]
#include <cmath>
#include <functional>
#include <iostream>

using Function = std::function<double(double*)>;
using std::size_t;

double Integrate(size_t, double*, double*, double*, Function, size_t = 0);
double IntegrateSequence(size_t, double*, double*, double*, Function);

#endif  // MODULES_TASK_3_KROTOV_A_INTEGR_RECT_INTEGR_RECT_H_
