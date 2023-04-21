// Copyright 2023 Nikiforova Lada
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include "../../../modules/task_1/nikiforova_l_trapezoidal_method/trapezoidal_method.h"

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
    double res = 0.0;
    std::vector<double> prm(dim);
    int j = 0;
    while (j < seg) {
        int k = j;
        int l = 0;
        while (l < dim) {
            prm[l] = front[l].first + dlt[l] * (k % p);
            k /= p;
            l++;
        }
        double trm = function(prm);
        int m = 0;
        while (m < dim) {
            if (prm[m] == front[m].first) {
                trm /= 2;
                }
            if (prm[m] == front[m].second) {
                trm /= 2;
                }
            m++;
        }
        res += trm;
        j++;
    }
    int n = 0;
    while (n < dim) {
        res *= dlt[n];
        n++;
    }
    return res;
}
