// Copyright 2023 Pinezhanin Evgeny
#include <ctime>
#include <random>
#include "../../../modules/task_1/pinezhanin_e_monte_carlo/monte_carlo.h"

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
