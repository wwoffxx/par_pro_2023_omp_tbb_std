// Copyright 2023 Krotov Aleksey
#include <gtest/gtest.h>
#include <omp.h>

#include <cmath>
#include <iostream>

#include "./integr_rect.h"

TEST(IntegralRectangle, Function1) {
    size_t dim = 1;
    auto step = new double{0.1};
    auto lower = new double{0.0};
    auto upper = new double{1.0};
    auto func = [](double* point) { return point[0]; };
    auto start_time = omp_get_wtime();
    auto result = Integrate(dim, step, lower, upper, func);
    auto end_time = omp_get_wtime();
    auto duration = (end_time - start_time) * 1000000;
    std::cout << "Time: " << duration << " us" << std::endl;
    delete step;
    delete lower;
    delete upper;
    ASSERT_DOUBLE_EQ(result, 0.45);
}

TEST(IntegralRectangle, Function2Step1) {
    size_t dim = 2;
    auto step = new double[2]{0.1, 0.1};
    auto lower = new double[2]{0.0, 0.0};
    auto upper = new double[2]{1.0, 1.0};
    auto func = [](double* point) -> double { return point[0] * point[1]; };
    auto start_time = omp_get_wtime();
    auto result = Integrate(dim, step, lower, upper, func);
    auto end_time = omp_get_wtime();
    auto duration = (end_time - start_time) * 1000000;
    std::cout << "Time: " << duration << " us" << std::endl;
    delete[] step;
    delete[] lower;
    delete[] upper;
    ASSERT_DOUBLE_EQ(result, 0.2025);
}

TEST(IntegralRectangle, Function2Step2) {
    size_t dim = 2;
    auto step = new double[2]{0.001, 0.001};
    auto lower = new double[2]{0.0, 0.0};
    auto upper = new double[2]{1.0, 1.0};
    auto func = [](double* point) -> double { return point[0] * point[1]; };
    auto start_time = omp_get_wtime();
    auto result = Integrate(dim, step, lower, upper, func);
    auto end_time = omp_get_wtime();
    auto duration = (end_time - start_time) * 1000000;
    std::cout << "Time: " << duration << " us" << std::endl;
    delete[] step;
    delete[] lower;
    delete[] upper;
    ASSERT_NEAR(result, 0.2495, 0.0001);
}

TEST(IntegralRectangle, Function3Step1) {
    size_t dim = 3;
    auto step = new double[3]{0.1, 0.1, 0.1};
    auto lower = new double[3]{0.0, 0.0, 0.0};
    auto upper = new double[3]{2.0, 1.5, 1.0};
    auto func = [](double* point) -> double {
        return std::sqrt(point[0]) * point[1] + point[2];
    };
    auto start_time = omp_get_wtime();
    auto result = Integrate(dim, step, lower, upper, func);
    auto end_time = omp_get_wtime();
    auto duration = (end_time - start_time) * 1000000;
    std::cout << "Time: " << duration << " us" << std::endl;
    delete[] step;
    delete[] lower;
    delete[] upper;
    ASSERT_NEAR(result, 3.249, 0.001);
}

TEST(IntegralRectangle, Function3Step2) {
    size_t dim = 2;
    auto step = new double[2]{0.1, 0.1};
    auto lower = new double[2]{0.0, 0.0};
    auto upper = new double[2]{1.0, 1.0};
    auto func = [](double* point) -> double { return point[0] * point[1]; };
    auto start_time = omp_get_wtime();
    auto result = Integrate(dim, step, lower, upper, func);
    auto end_time = omp_get_wtime();
    auto duration = (end_time - start_time) * 1000000;
    std::cout << "Time: " << duration << " us" << std::endl;
    delete[] step;
    delete[] lower;
    delete[] upper;
    ASSERT_DOUBLE_EQ(result, 0.2025);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
