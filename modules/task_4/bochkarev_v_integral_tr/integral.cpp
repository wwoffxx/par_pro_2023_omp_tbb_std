// Copyright 2023 Bochkarev Vladimir
#include <functional>
#include <vector>
// #include <thread>
// #include <mutex>
// #include <future>
#include "../../../modules/task_4/bochkarev_v_integral_tr/integral.h"
#include "../../../3rdparty/unapproved/unapproved.h"

// std::mutex critic;

double calc_seq(double a, double c, double e,
const double hx, const double hy, const double hz,
int n, int begin, int end,
const std::function<double(double, double, double)> &fun) {
    double local_res = 0;
    for (int i = begin; i < end; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) {
                const double x1 = a + i*hx;
                const double x2 = a + (i+1)*hx;

                const double y1 = c + j*hy;
                const double y2 = c + (j+1)*hy;

                const double z1 = e + k*hz;
                const double z2 = e + (k+1)*hz;

                local_res+=0.5*(x2-x1)*(y2-y1)*(z2-z1)*(fun(x1, y1, z1)+fun(x2, y2, z2));
            }
    return local_res;
}

void calc(double a, double c, double e,
const double hx, const double hy, const double hz,
int n, int begin, int end, std::promise<double> &&pr,
const std::function<double(double, double, double)> &fun) {
    double local_res = 0;
    for (int i = begin; i < end; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) {
                const double x1 = a + i*hx;
                const double x2 = a + (i+1)*hx;

                const double y1 = c + j*hy;
                const double y2 = c + (j+1)*hy;

                const double z1 = e + k*hz;
                const double z2 = e + (k+1)*hz;

                // std::lock_guard<std::mutex> lock(critic);
                local_res+=0.5*(x2-x1)*(y2-y1)*(z2-z1)*(fun(x1, y1, z1)+fun(x2, y2, z2));
            }
    pr.set_value(local_res);
}

double integral3D(double a, double b, double c, double d, double e,
double f, int n, const std::function<double(double, double, double)> &fun) {
    const double hx = (b-a)/n;
    const double hy = (d-c)/n;
    const double hz = (f-e)/n;
    const int nthreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(nthreads);
    std::promise<double> *promises = new std::promise<double>[nthreads];
    std::future<double> *futures = new std::future<double>[nthreads];
    double res = 0;
    const int delta = n / nthreads;
    for (int t = 0; t < nthreads; t++) {
        futures[t] = promises[t].get_future();
        threads[t] = std::thread(calc, a, c, e, hx, hy, hz, n,
        t*delta, (t+1)*delta, std::move(promises[t]), fun);
        threads[t].join();
        res += futures[t].get();
    }
    if (n % nthreads != 0) {
        int begin = delta*nthreads;
        int end = delta*nthreads + n % nthreads;
        res += calc_seq(a, c, e, hx, hy, hz, n, begin, end, fun);
    }
    delete []promises;
    delete []futures;
    return res;
}
