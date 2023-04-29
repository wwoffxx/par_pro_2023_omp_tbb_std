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
    std::vector<std::vector<int>> sourceImg = getRandomImg(30, 30);
    std::vector<std::vector<int>> resultImg = GaussianFilter(sourceImg);

    EXPECT_FALSE(imgEquivalent(sourceImg, resultImg));
}

TEST(Gaussian, can_process_image_2) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(15, 45);
    std::vector<std::vector<int>> resultImg = GaussianFilter(sourceImg);

    EXPECT_FALSE(imgEquivalent(sourceImg, resultImg));
}

TEST(Gaussian, can_process_image_correctly) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(10, 10);
    std::vector<std::vector<int>> resultImg1 = GaussianFilter(sourceImg);
    std::vector<std::vector<int>> resultImg2 = GaussianFilter(sourceImg);

    EXPECT_TRUE(imgEquivalent(resultImg1, resultImg2));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
