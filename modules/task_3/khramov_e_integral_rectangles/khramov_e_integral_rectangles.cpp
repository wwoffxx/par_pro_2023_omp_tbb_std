// Copyright 2023 Khramov Egor
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range3d.h>
#include "../../../modules/task_3/khramov_e_integral_rectangles/khramov_e_integral_rectangles.h"


struct IntegrateBody {
    IntegralFunction func;
    double a[3];
    double h[3];
    double result;

    IntegrateBody(IntegralFunction func, double a[3], double h[3]) :
        func(func), result(0.0) {
        for (int i = 0; i < 3; i++) {
            this->a[i] = a[i];
            this->h[i] = h[i];
        }
    }

    IntegrateBody(IntegrateBody& other, tbb::split) :
        func(other.func), result(0.0) {
        for (int i = 0; i < 3; i++) {
            this->a[i] = other.a[i];
            this->h[i] = other.h[i];
        }
    }

    void operator()(const tbb::blocked_range3d<int, int, int>& r) {
        for (int i = r.pages().begin(); i != r.pages().end(); ++i) {
            for (int j = r.rows().begin(); j != r.rows().end(); ++j) {
                for (int k = r.cols().begin(); k != r.cols().end(); ++k) {
                    double x = a[0] + h[0] * i;
                    double y = a[1] + h[1] * j;
                    double z = a[2] + h[2] * k;
                    double value = getRectangleValue(func, x, y, z, h);
                    result += h[0] * h[1] * h[2] * value;
                }
            }
        }
    }

    void join(const IntegrateBody& other) {
        result += other.result;
    }
};


double getRectangleValue(IntegralFunction f, double x, double y, double z, double* h) {
    return f(x + h[0] / 2, y + h[1] / 2, z + h[2] / 2);
}

double integrateSequential(IntegralFunction func, double a[3], double b[3], int n[3]) {
    double result = 0.0;

    double h[3];
    for (int i = 0; i < 3; i++) {
        h[i] = (b[i] - a[i]) / n[i];
    }

    for (int i = 0; i < n[0]; i++) {
        for (int j = 0; j < n[1]; j++) {
            for (int k = 0; k < n[2]; k++) {
                double x = a[0] + h[0] * i;
                double y = a[1] + h[1] * j;
                double z = a[2] + h[2] * k;
                double value = getRectangleValue(func, x, y, z, h);
                result += h[0] * h[1] * h[2] * value;
            }
        }
    }

    return result;
}

double integrateParallel(IntegralFunction func, double a[3], double b[3], int n[3]) {
    double result = 0.0;

    double h[3];
    for (int i = 0; i < 3; i++) {
        h[i] = (b[i] - a[i]) / n[i];
    }

    IntegrateBody body(func, a, h);
    tbb::parallel_reduce(tbb::blocked_range3d<int, int, int>(0, n[0], 0, n[1], 0, n[2]), body);

    result = body.result;

    return result;
}