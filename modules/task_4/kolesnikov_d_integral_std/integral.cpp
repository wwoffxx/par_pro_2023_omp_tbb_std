// Copyright 2023 Kolesnikov Denis


#include "../../../modules/task_4/kolesnikov_d_integral_std/integral.h"

double integral_worker(
  double (*f)(std::vector<double>),
  const std::vector<std::pair<double, double>>& bounds,
  int n,
  int start_i,
  int end_i
) {
  double hx = (bounds[0].second - bounds[0].first) / n;
  double hy = (bounds[1].second - bounds[1].first) / n;
  double hz = (bounds[2].second - bounds[2].first) / n;

  double integral_res = 0;
  for (int i = start_i; i < end_i; i++) {
    for (int j = 0; j < n; j++) {
      for (int m = 0; m < n; m++) {
        double x1 = bounds[0].first + i*hx;
        double x2 = bounds[0].first + (i+1)*hx;
        double y1 = bounds[1].first + j*hy;
        double y2 = bounds[1].first + (j+1)*hy;
        double z1 = bounds[2].first + m*hz;
        double z2 = bounds[2].first + (m+1)*hz;
        integral_res +=
            0.5*(x2-x1)*(y2-y1)*(z2-z1)*(f({x1, y1, z1}) + f({x2, y2, z2}));
      }
    }
  }
  return integral_res;
}

double integral(
  double (*f)(std::vector<double>),
  const std::vector<std::pair<double, double>>& bounds,
  int n
) {
  int num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads(num_threads);
  std::vector<double> results(num_threads, 0.0);

  int chunk_size = n / num_threads;
  int remaining = n % num_threads;
  int start_i = 0;
  int end_i = 0;

  for (int i = 0; i < num_threads; i++) {
    start_i = end_i;
    end_i = start_i + chunk_size;
    if (i < remaining)
      end_i++;

    threads[i] = std::thread(
      [&](int i, int start_i, int end_i) {
        results[i] = integral_worker(f, bounds, n, start_i, end_i);
      },
      i, start_i, end_i);
  }

  for (int i = 0; i < num_threads; i++) {
    threads[i].join();
  }

  double integral_res = 0.0;
  for (int i = 0; i < num_threads; i++) {
    integral_res += results[i];
  }

  return integral_res;
}
