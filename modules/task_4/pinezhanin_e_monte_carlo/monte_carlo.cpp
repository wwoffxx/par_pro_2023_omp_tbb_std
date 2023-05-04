// Copyright 2023 Pinezhanin Evgeny
#include <tbb/tbb.h>
#include <random>
#include "../../../modules/task_3/pinezhanin_e_monte_carlo/monte_carlo.h"
#include "../../../3rdparty/unapproved/unapproved.h"

double getIntegralMonteCarlo(const std::function<double(const std::vector<double>&)>& f,
                             std::vector<double> a, std::vector<double> b, int number_points) {
    int dimension = static_cast<int>(a.size());
    std::mt19937 gen;
    std::vector<std::uniform_real_distribution<double>> uniform_distribution(dimension);
    std::vector<double> point(dimension);
    double result = 0.0;

    for (int i = 0; i < dimension; i++) {
        uniform_distribution[i] = std::uniform_real_distribution<double>(a[i], b[i]);
    }

    for (int i = 0; i < number_points; i++) {
        for (int j = 0; j < dimension; j++) {
            point[j] = uniform_distribution[j](gen);
        }
        result += f(point);
    }
    for (int i = 0; i < dimension; i++) {
        result *= (b[i] - a[i]);
    }
    result /= number_points;

    return result;
}

double getIntegralMonteCarloStd(const std::function<double(const std::vector<double>&)>& f,
                                std::vector<double> a, std::vector<double> b, int number_points) {
    int dimension = static_cast<int>(a.size());
    std::vector<std::uniform_real_distribution<double>> uniform_distribution(dimension);
    double result = 0.0;

    for (int i = 0; i < dimension; i++) {
        uniform_distribution[i] = std::uniform_real_distribution<double>(a[i], b[i]);
    }

    const int numberThreads = std::thread::hardware_concurrency();
    std::vector<std::promise<int>> promises(numberThreads);
    std::vector<std::future<int>> futures(nthreads);
    std::vector<std::thread> threads(numberThreads);

    for (int i = 0; i < numberThreads; i++) {
        futures[i] = promises[i].get_future();
        threads[i] = std::thread([] () {

        }, tmp_vec, ops, std::move(promises[i]));
        threads[i].join();
        result += futures[i].get();
    }

    result = tbb::parallel_reduce(tbb::blocked_range<size_t>(0, number_points), 0.0,
        [&] (tbb::blocked_range<size_t> range, double res) {

            for (size_t i = range.begin(); i != range.end(); ++i) {
                for (int j = 0; j < dimension; j++) {
                    point[j] = uniform_distribution[j](gen);
                }
                res += f(point);
            }
            return res;
        },
        [] (double x, double y) -> double {
            return x + y;
        },
        tbb::auto_partitioner());

    for (int i = 0; i < dimension; i++) {
        result *= (b[i] - a[i]);
    }
    result /= number_points;

    return result;
}
