// Copyright 2023 Kolesnikov Denis
#ifndef MODULES_TASK_3_KOLESNIKOV_D_INTEGRAL_TBB_INTEGRAL_H_
#define MODULES_TASK_3_KOLESNIKOV_D_INTEGRAL_TBB_INTEGRAL_H_

#include <tbb/tbb.h>
#include <time.h>
#include <functional>
#include <iostream>

double integral(const std::vector<std::pair<double, double>>& bounds,
 int n, double (*func)(std::vector<double>));

#endif  // MODULES_TASK_3_KOLESNIKOV_D_INTEGRAL_TBB_INTEGRAL_H_
