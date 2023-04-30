// Copyright 2023 Kiselev Vladislav
#include <gtest/gtest.h>
#include "./vert_gaussian.h"

TEST(Gaussian, can_create_matrix) {
    std::vector<std::vector<int>> img;

    ASSERT_NO_THROW(img = getRandomImg(10, 10));
}

TEST(Gaussian, cant_create_matrix_with_wrong_size) {
    std::vector<std::vector<int>> img;

    ASSERT_ANY_THROW(img = getRandomImg(0, 20));
    ASSERT_ANY_THROW(img = getRandomImg(15, 0));
    ASSERT_ANY_THROW(img = getRandomImg(-5, -5));
    ASSERT_ANY_THROW(img = getRandomImg(-3, 0));
}

TEST(Gaussian, can_create_kernel) {
    std::vector<std::vector<double>> sourceKernel =
    { { 0.075113607954111511, 0.12384140315297398, 0.075113607954111511 },
      { 0.12384140315297398, 0.20417995557165811,  0.12384140315297398 },
      { 0.075113607954111511, 0.12384140315297398, 0.075113607954111511 } };

    std::vector<std::vector<double>> kernel = createGaussian();

    EXPECT_TRUE(imgEquivalent(sourceKernel, kernel));
}


TEST(Gaussian, can_process_image_1) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(10, 10);

    double t_start, dt_1, dt_2;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = omp_get_wtime() - t_start;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_par = GaussianFilter_Par(sourceImg);
    dt_2 = omp_get_wtime() - t_start;

    std::cout << "eff = " << dt_2 / dt_1;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

TEST(Gaussian, can_process_image_2) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(20, 20);

    double t_start, dt_1, dt_2;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = omp_get_wtime() - t_start;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_par = GaussianFilter_Par(sourceImg);
    dt_2 = omp_get_wtime() - t_start;

    std::cout << "eff = " << dt_2 / dt_1;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

TEST(Gaussian, can_process_image_3) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(30, 30);

    double t_start, dt_1, dt_2;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = omp_get_wtime() - t_start;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_par = GaussianFilter_Par(sourceImg);
    dt_2 = omp_get_wtime() - t_start;

    std::cout << "eff = " << dt_2 / dt_1;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

TEST(Gaussian, can_process_image_4) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(40, 40);

    double t_start, dt_1, dt_2;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = omp_get_wtime() - t_start;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_par = GaussianFilter_Par(sourceImg);
    dt_2 = omp_get_wtime() - t_start;

    std::cout << "eff = " << dt_2 / dt_1;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

TEST(Gaussian, can_process_image_5) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(100, 100);

    double t_start, dt_1, dt_2;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = omp_get_wtime() - t_start;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_par = GaussianFilter_Par(sourceImg);
    dt_2 = omp_get_wtime() - t_start;

    std::cout << "eff = " << dt_2 / dt_1;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

TEST(Gaussian, can_process_image_6) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(50, 100);

    double t_start, dt_1, dt_2;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = omp_get_wtime() - t_start;

    t_start = omp_get_wtime();
    std::vector<std::vector<int>> resultImg_par = GaussianFilter_Par(sourceImg);
    dt_2 = omp_get_wtime() - t_start;

    std::cout << "eff = " << dt_2 / dt_1;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
