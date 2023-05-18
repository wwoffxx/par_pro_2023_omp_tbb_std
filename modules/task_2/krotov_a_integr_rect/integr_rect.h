// Copyright 2023 Krotov Aleksey
#ifndef MODULES_TASK_2_KROTOV_A_INTEGR_RECT_INTEGR_RECT_H_
#define MODULES_TASK_2_KROTOV_A_INTEGR_RECT_INTEGR_RECT_H_

#include <functional>

using Function = std::function<double(double*)>;
using std::size_t;

double Integrate(size_t, double*, double*, double*, Function);

#endif  // MODULES_TASK_2_KROTOV_A_INTEGR_RECT_INTEGR_RECT_H_
