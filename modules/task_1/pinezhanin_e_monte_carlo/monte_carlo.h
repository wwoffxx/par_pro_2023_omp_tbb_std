// Copyright 2023 Pinezhanin Evgeny
#ifndef MODULES_TASK_1_PINEZHANIN_E_MONTE_CARLO_MONTE_CARLO_H_
#define MODULES_TASK_1_PINEZHANIN_E_MONTE_CARLO_MONTE_CARLO_H_

#include <vector>
#include <functional>

double getIntegralMonteCarlo(const std::function<double(const std::vector<double>&)>& f,
                             std::vector<double> a, std::vector<double> b, int number_points);

#endif  // MODULES_TASK_1_PINEZHANIN_E_MONTE_CARLO_MONTE_CARLO_H_
