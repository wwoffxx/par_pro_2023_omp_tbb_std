// Copyright 2023 Churkin Aleksandr
#include <gtest/gtest.h>
#include "./convhulls_bin.h"

TEST(ConvHullsBin, Test_1_Image_10X10_Corners) {
    const int M = 10, N = 10;
    std::vector<int> image({
    1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
    });

    MarkComponents(&image, M, N);
    auto hulls = LeaveOnlyHulls(&image, M, N);

    // PrintImage(image, M, N);

    std::vector<int> correctResult({
    1, 0, 1, 0, 0, 0, 2, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 3, 0, 0, 0, 0, 4, 0, 4,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 3, 0, 0, 4, 0, 0, 0, 4,
    });
    EXPECT_EQ(image, correctResult);
}

TEST(ConvHullsBin, Test_2_Image_10X10_Empty) {
    const int M = 10, N = 10;
    std::vector<int> image({
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    });

    MarkComponents(&image, M, N);
    auto hulls = LeaveOnlyHulls(&image, M, N);

    EXPECT_EQ(hulls.size(), 0);
}

TEST(ConvHullsBin, Test_3_Image_5X10) {
    const int M = 5, N = 10;
    std::vector<int> image({
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 1, 0, 0, 0, 0,
    });

    MarkComponents(&image, M, N);
    auto hulls = LeaveOnlyHulls(&image, M, N);

    // PrintImage(image, M, N);

    std::vector<int> correctResult({
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 1, 0, 0, 0, 0,
    });

    EXPECT_EQ(image, correctResult);
}

TEST(ConvHullsBin, Test_4_WillNotFailOnRandomImage_10X10) {
    const int M = 10, N = 10;
    std::vector<int> image = GetRandomBinImage(M, N);

    MarkComponents(&image, M, N);
    auto hulls = LeaveOnlyHulls(&image, M, N);
}

TEST(ConvHullsBin, Test_5_WillNotFailOnRandomImage_40X50) {
    const int M = 40, N = 50;
    std::vector<int> image = GetRandomBinImage(M, N);

    MarkComponents(&image, M, N);
    auto hulls = LeaveOnlyHulls(&image, M, N);
}
