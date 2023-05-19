// Copyright 2023 Mironov Nikita
#include <gtest/gtest.h>
#include "../../../modules/task_2/mironov_n_trapezoid_method_omp/trapezoid.h"

double f1(std::vector<double> values) {
    double x = values[0];
    return x*x;
}

double f2(std::vector<double> values) {
    double x = values[0];
    double y = values[1];
    return x*y;
}

double f3(std::vector<double> values) {
    double x = values[0];
    double y = values[1];
    double z = values[2];
    return (x * y) + z;
}

double f4(std::vector<double> values) {
    double x = values[0];
    double y = values[1];
    double z = values[2];
    return sqrt((x*x) + y - z);
}

TEST(trapezoid, d1_test_omp) {
    std::vector<std::pair<double, double>> bounds(3);
    bounds[0] = {1, 3};
    bounds[1] = {1, 3};
    bounds[2] = {1, 3};
    int dimensions = 1;
    double integration_result = 104.0/3.0;
    double method_result = trapezoid_method(f1, bounds, 100);
    double tolerance = 0.15;

    ASSERT_NEAR(method_result, integration_result, tolerance);
}

TEST(trapezoid, d2_test_omp) {
    std::vector<std::pair<double, double>> bounds(3);
    bounds[0] = {3, 8};
    bounds[1] = {1, 4};
    bounds[2] = {3, 6};
    int dimensions = 2;
    double integration_result = 618.75;
    double method_result = trapezoid_method(f2, bounds, 100);
    double tolerance = 0.15;

    ASSERT_NEAR(method_result, integration_result, tolerance);
}

TEST(trapezoid, d3_test_1_omp) {
    std::vector<std::pair<double, double>> bounds(3);
    bounds[0] = {1, 5};
    bounds[1] = {1, 4};
    bounds[2] = {1, 6};
    int dimensions = 3;
    double integration_result = 660;
    double method_result = trapezoid_method(f3, bounds, 100);
    double tolerance = 0.15;

    ASSERT_NEAR(method_result, integration_result, tolerance);
}

TEST(trapezoid, d3_test_2_omp) {
    std::vector<std::pair<double, double>> bounds(3);
    bounds[0] = {3, 8};
    bounds[1] = {1, 4};
    bounds[2] = {0, 9};
    int dimensions = 3;
    double integration_result = 713.775;
    double method_result = trapezoid_method(f4, bounds, 100);
    double tolerance = 0.15;

    ASSERT_NEAR(method_result, integration_result, tolerance);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
