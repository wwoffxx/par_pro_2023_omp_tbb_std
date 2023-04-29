// Copyright 2023 Melnik Denis
#include <gtest/gtest.h>
#include "../../../modules/task_1/melnik_d_block_gauss_filter/block_gauss_filter.h"


TEST(Gauss_Filter_Seq, Test1_3x3) {
    Image image(3, 3);
    int arr[] = {100, 100, 100, 0, 0, 0, 100, 100, 100};
    image.Load(arr);

    Image res(3, 3);
    int resArr[] = {75, 75, 75, 50, 50, 50, 75, 75, 75};
    res.Load(resArr);

    Image handled = GaussFilter(image);

    ASSERT_EQ(res, handled);
}

TEST(Gauss_Filter_Seq, Test2_4x4) {
    Image image(4, 4);
    int arr[] = {100, 100, 100, 100, 50, 50, 50, 50,
                 20,  20,  20,  20,  0,  0,  0,  0};
    image.Load(arr);

    Image res(4, 4);

    int resArr[] = {87, 87, 87, 87, 55, 55, 55, 55, 22, 22, 22, 22, 5, 5, 5, 5};
    res.Load(resArr);

    Image handled = GaussFilter(image);

    ASSERT_EQ(res, handled);
}

TEST(Gauss_Filter_Seq, Test3_5x3) {
    Image image(5, 3);
    int arr[] = {100, 100, 100, 100, 50, 50, 50, 50, 0, 0, 50, 50, 0, 0, 0};
    image.Load(arr);

    Image res(5, 3);
    int resArr[] = {87, 87, 84, 68, 46, 62, 59, 46, 28, 15, 50, 40, 18, 3, 0};
    res.Load(resArr);

    Image handled = GaussFilter(image);

    ASSERT_EQ(res, handled);
}

TEST(Gauss_Filter_Seq, Test4_4x5) {
    Image image(4, 5);
    int arr[] = {100, 0, 100, 0, 80, 0, 80, 0, 60, 0,
                 60,  0, 40,  0, 40, 0, 20, 0, 20, 0};
    image.Load(arr);

    Image res(4, 5);
    int resArr[] = {71, 47, 47, 23, 60, 40, 40, 20, 45, 30,
                    30, 15, 30, 20, 20, 10, 18, 12, 12, 6};
    res.Load(resArr);

    Image handled = GaussFilter(image);

    ASSERT_EQ(res, handled);
}

TEST(Gauss_Filter_Seq, Test5_5x5) {
    Image image(5, 5);
    int arr[] = {100, 0,  100, 0, 20, 80, 0,  80, 0, 40, 60, 0,  60,
                 0,   60, 40,  0, 40, 0,  80, 20, 0, 20, 0,  100};
    image.Load(arr);

    Image res(5, 5);
    int resArr[] = {71, 47, 47, 30, 18, 60, 40, 40, 30, 30, 45, 30, 30,
                    30, 45, 30, 20, 20, 30, 60, 18, 12, 12, 30, 71};
    res.Load(resArr);

    Image handled = GaussFilter(image);

    ASSERT_EQ(res, handled);
}
