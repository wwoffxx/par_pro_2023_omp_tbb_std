// Copyright 2023 Terentiev Alexander
#include <gtest/gtest.h>
#include "../../../modules/task_3/terentiev_a_trapez_integral/trapez_integral.h"


TEST(Trapez_Integral, Test1_seq) {
    ASSERT_TRUE(Testing(0, 0, 0, 3, 2, 1, Func1, 4.5));
}

TEST(Trapez_Integral, Test2_seq) {
    ASSERT_TRUE(Testing(1, 1, 1, 2, 2, 2, Func1, 3.375));
}

TEST(Trapez_Integral, Test3_seq) {
    ASSERT_TRUE(Testing(5, 0, 1, 7, 3, 2, Func1, 81));
}

TEST(Trapez_Integral, Test4_seq) {
    ASSERT_TRUE(Testing(1, 1, 1, 2, 2, 2, Func2, 0.33302));
}

TEST(Trapez_Integral, Test5_seq) {
    ASSERT_TRUE(Testing(1, 2, 3, 7, 6, 5, Func2, 1.092));
}

TEST(Trapez_Integral, Test1_par) {
    double par = TrapezIntegral3DParallel(0, 0, 0, 3, 2, 1, Steps, Func1);
    double seq = TrapezIntegral3D(0, 0, 0, 3, 2, 1, Steps, Func1);
    ASSERT_EQ(par, seq);
}

TEST(Trapez_Integral, Test2_par) {
    double par = TrapezIntegral3DParallel(1, 1, 1, 2, 2, 2, Steps, Func1);
    double seq = TrapezIntegral3D(1, 1, 1, 2, 2, 2, Steps, Func1);
    ASSERT_EQ(par, seq);
}

TEST(Trapez_Integral, Test3_par) {
    double par = TrapezIntegral3DParallel(5, 0, 1, 7, 3, 2, Steps, Func1);
    double seq = TrapezIntegral3D(5, 0, 1, 7, 3, 2, Steps, Func1);
    ASSERT_EQ(par, seq);
}

TEST(Trapez_Integral, Test4_par) {
    double par = TrapezIntegral3DParallel(1, 1, 1, 2, 2, 2, Steps, Func2);
    double seq = TrapezIntegral3D(1, 1, 1, 2, 2, 2, Steps, Func2);
    ASSERT_EQ(par, seq);
}

TEST(Trapez_Integral, Test5_par) {
    double par = TrapezIntegral3DParallel(1, 2, 3, 7, 6, 5, Steps, Func2);
    double seq = TrapezIntegral3D(1, 2, 3, 7, 6, 5, Steps, Func2);
    ASSERT_EQ(par, seq);
}
