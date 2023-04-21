// Copyright 2023 Pinezhanin Evgeny
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "./monte_carlo.h"

const double relative_error = 0.01;

TEST(Monte_Carlo_seq, Test_one_dimension) {
    const std::function<double(const std::vector<double>)> f =
        [](const std::vector<double>& x) -> double { return x[0] * x[0]; };
    std::vector<double> a = { 0.0 }, b = { 10.0 };
    int number_points = 1000000;
    double exact_value_integral = 1000.0 / 3.0;

    double calc_value_integral = getIntegralMonteCarlo(f, a, b, number_points);
    double error = std::abs(calc_value_integral - exact_value_integral) / std::abs(exact_value_integral);

    ASSERT_LE(error, relative_error);
}

TEST(Monte_Carlo_seq, Test_two_dimension) {
    const std::function<double(const std::vector<double>)> f =
        [](const std::vector<double>& x) -> double { return x[0] * x[0] + x[1] * x[1]; };
    std::vector<double> a = { 0.0, -1.0 }, b = { 5.0, 1.0 };
    int number_points = 1000000;
    double exact_value_integral = 260.0 / 3.0;

    double calc_value_integral = getIntegralMonteCarlo(f, a, b, number_points);
    double error = std::abs(calc_value_integral - exact_value_integral) / std::abs(exact_value_integral);

    ASSERT_LE(error, relative_error);
}

TEST(Monte_Carlo_seq, Test_three_dimension) {
    const std::function<double(const std::vector<double>)> f =
        [](const std::vector<double>& x) -> double { return x[0] * x[1] * x[1] * x[2] + x[1] * x[2] / 2.0; };
    std::vector<double> a = { 0.0, -1.0, 5.0 }, b = { 5.0, 1.0, 10.0 };
    int number_points = 1000000;
    double exact_value_integral = 625.0 / 2.0;

    double calc_value_integral = getIntegralMonteCarlo(f, a, b, number_points);
    double error = std::abs(calc_value_integral - exact_value_integral) / std::abs(exact_value_integral);

    ASSERT_LE(error, relative_error);
}

TEST(Monte_Carlo_seq, Test_four_dimension) {
    const std::function<double(const std::vector<double>)> f =
            [](const std::vector<double>& x) -> double {
                return std::exp(x[0]) * x[1] * x[1] * std::pow(x[3], 5) -
                       std::exp(x[1]) * x[0] / x[2] + x[1] / std::pow(x[0], 3);
            };
    std::vector<double> a = { 1.0, -1.0, 5.0, -10.0 }, b = { 5.0, 1.0, 10.0, -9.0 };
    int number_points = 1000000;
    double exact_value_integral = (std::pow(9.0, 6.0) - std::pow(10.0, 6.0)) * 5.0 / 9.0 *
                                  (std::exp(5.0) - std::exp(1.0)) + 12.0 * std::log(2.0) *
                                  (1.0 / std::exp(1.0) - std::exp(1.0));

    double calc_value_integral = getIntegralMonteCarlo(f, a, b, number_points);
    double error = std::abs(calc_value_integral - exact_value_integral) / std::abs(exact_value_integral);

    ASSERT_LE(error, relative_error);
}

TEST(Monte_Carlo_seq, Test_five_dimension) {
    const std::function<double(const std::vector<double>)> f =
            [](const std::vector<double>& x) -> double {
                return std::exp(x[0]) * x[1] * x[1] * std::pow(x[3], 5) - std::exp(x[1]) * x[0] * x[4] * x[4] / x[2] +
                       x[1] / std::pow(x[0], 3);
            };
    std::vector<double> a = { 1.0, -1.0, 5.0, -10.0, -3.0 }, b = { 5.0, 1.0, 10.0, -9.0, 5.0 };
    int number_points = 1000000;
    double exact_value_integral = (std::pow(9.0, 6.0) - std::pow(10.0, 6.0)) * 5.0 / 9.0 *
                                  (std::exp(5.0) - std::exp(1.0)) * 8.0 + 12.0 * (std::pow(5.0, 3.0) +
                                  std::pow(3.0, 3.0)) / 3.0 * std::log(2.0) * (1.0 / std::exp(1.0) - std::exp(1.0));

    double calc_value_integral = getIntegralMonteCarlo(f, a, b, number_points);
    double error = std::abs(calc_value_integral - exact_value_integral) / std::abs(exact_value_integral);

    ASSERT_LE(error, relative_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
