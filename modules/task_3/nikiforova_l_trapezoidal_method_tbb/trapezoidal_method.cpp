// Copyright 2023 Nikiforova Lada
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>
#include <utility>
#include "tbb/tbb.h"
#include "../../../modules/task_3/nikiforova_l_trapezoidal_method_tbb/trapezoidal_method.h"

double trapezoidalMethod(double (*function)(std::vector<double>),
             std::vector<std::pair<double, double>> front, int p) {
    int dim = front.size();
    int seg = 1;
    std::vector<double> dlt(dim);
    int i = 0;
    while (i < dim) {
        dlt[i] = (front[i].second - front[i].first) / p;
        seg *= p;
        i++;
    }
    double result = tbb::parallel_reduce(tbb::blocked_range<int>(0, seg), 0.0,
        [&](tbb::blocked_range<int> r, double res) {
            for (int i = r.begin(); i != r.end(); i++) {
                std::vector<double> prm(dim);
                int k = i;
                for (int j = 0; j < dim; j++) {
                    prm[j] = front[j].first + dlt[j] * (k % p);
                    k /= p;
                }
                double trm = function(prm);
                for (int j = 0; j < dim; j++) {
                    if (prm[j] == front[j].first) {
                        trm /= 2;
                    }
                    if (prm[j] == front[j].second) {
                        trm /= 2;
                    }
                }
                res += trm;
            }
            return res;
        }, std::plus<double>());

    int n = 0;
    while (n < dim) {
        result *= dlt[n];
        n++;
    }
    return result;
}
