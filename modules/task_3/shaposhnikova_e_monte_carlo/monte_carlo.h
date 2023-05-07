// Copyright 2023 Shaposhnikova Ekaterina
#ifndef MODULES_TASK_3_SHAPOSHNIKOVA_E_MONTE_CARLO_MONTE_CARLO_H_
#define MODULES_TASK_3_SHAPOSHNIKOVA_E_MONTE_CARLO_MONTE_CARLO_H_

#include <vector>

double MonteCarloSeq(std::vector<double> a,
  std::vector<double> b, int n, double func(double, double, double));
double MonteCarloParallelTbb(std::vector<double> a,
  std::vector<double> b, int n, double func(double, double, double));

#endif  // MODULES_TASK_3_SHAPOSHNIKOVA_E_MONTE_CARLO_MONTE_CARLO_H_
