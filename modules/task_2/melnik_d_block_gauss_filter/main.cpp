// Copyright 2023 Melnik Denis
#include <gtest/gtest.h>
#include "../../../modules/task_2/melnik_d_block_gauss_filter/block_gauss_filter.h"


TEST(Gauss_Filter_Seq, Test1_3x3) {
    Image origin(3, 3);
    origin.FillRandom();

    Image par = GaussFilterBlockParallel(origin);
    Image seq = GaussFilter(origin);

    ASSERT_EQ(par, seq);
}

TEST(Gauss_Filter_Seq, Test2_10x5) {
    Image origin(10, 5);
    origin.FillRandom();

    Image par = GaussFilterBlockParallel(origin);
    Image seq = GaussFilter(origin);

    ASSERT_EQ(par, seq);
}

TEST(Gauss_Filter_Seq, Test3_20x25) {
    Image origin(20, 25);
    origin.FillRandom();

    Image par = GaussFilterBlockParallel(origin);
    Image seq = GaussFilter(origin);

    ASSERT_EQ(par, seq);
}

TEST(Gauss_Filter_Seq, Test4_40x50) {
    Image origin(40, 50);
    origin.FillRandom();

    Image par = GaussFilterBlockParallel(origin);
    Image seq = GaussFilter(origin);

    ASSERT_EQ(par, seq);
}

TEST(Gauss_Filter_Seq, Test5_100x100) {
    Image origin(100, 100);
    origin.FillRandom();

    Image par = GaussFilterBlockParallel(origin);
    Image seq = GaussFilter(origin);

    ASSERT_EQ(par, seq);
}
