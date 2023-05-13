// Copyright 2023 Shaposhnikova Ekaterina
#include <tbb/tbb.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../../../modules/task_3/shaposhnikova_e_monte_carlo/monte_carlo.h"

double MonteCarloSeq(std::vector<double> a,
  std::vector<double> b, int n, double func(double, double, double)) {
  double sum = 0;
  double integral = 0;
  std::vector<double> x(3);
  double v = 1;
  std::mt19937_64 generator{ std::random_device {}() };
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  for (int i = 0; i < 3; i++) {
    v *= (b[i] - a[i]);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      x[j] = a[j] + (b[j] - a[j]) * distribution(generator);
    }
    sum += func(x[0], x[1], x[2]);
  }
  integral = sum * v / n;
  return integral;
}

double MonteCarloParallelTbb(std::vector<double> a,
  std::vector<double> b, int n, double func(double, double, double)) {
  double resSum = 0;
  double integral = 0;
  double v = 1;
  std::mt19937_64 generator{ std::random_device {}() };
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  for (int i = 0; i < 3; i++) {
    v *= (b[i] - a[i]);
  }

  resSum = tbb::parallel_reduce(
    tbb::blocked_range<int>(0, n), 0.0,
    [&](tbb::blocked_range<int> r, double sum){
    std::vector<double> x(3);
      for (int i = r.begin(); i < r.end(); ++i) {
        for (int j = 0; j < 3; ++j) {
          x[j] = a[j] + (b[j] - a[j]) * distribution(generator);
        }
        sum += func(x[0], x[1], x[2]);
      }
      return sum;
    },
    std::plus<double>());

  integral = resSum * v / n;
  return integral;
}
