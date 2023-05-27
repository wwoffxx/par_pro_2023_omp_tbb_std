// Copyright 2023 Kolesnikov Denis
#ifndef MODULES_TASK_2_KOLESNIKOV_D_INTEGRAL_OMP_INTEGRAL_H_
#define MODULES_TASK_2_KOLESNIKOV_D_INTEGRAL_OMP_INTEGRAL_H_

#include <omp.h>
#include <vector>
#include <utility>

double integral(
  double f(std::vector<double>),
  const std::vector<std::pair<double, double>>& bounds,
  int n
);


#endif  // MODULES_TASK_2_KOLESNIKOV_D_INTEGRAL_OMP_INTEGRAL_H_
