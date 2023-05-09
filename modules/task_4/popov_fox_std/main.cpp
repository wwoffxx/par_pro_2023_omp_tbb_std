// Copyright 2023 Popov Andrey
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <cmath>
#include "../../../3rdparty/unapproved/unapproved.h"
#include "../popov_fox_std/popov_fox_std.h"

TEST(Parallel_Operations_Std_Threads, Test_Addition) {
    const int nthreads = std::thread::hardware_concurrency() * 10;
  std::vector<int> vector = getrandvect(nthreads);
    int serial_add = getserialOps(vector, "+");
  int approp_add = getappropOps(vector, "+");
    ASSERT_EQ(serial_add, approp_add);
}

TEST(Parallel_Operations_Std_Threads, Test_Addition_2) {
    const int nthreads = std::thread::hardware_concurrency() * 11;
    std::vector<int> vector = getrandvect(nthreads);
    int serial_add = getserialOps(vector, "+");
    int approp_add = getappropOps(vector, "+");
    ASSERT_EQ(serial_add, approp_add);
}

TEST(Parallel_Operations_Std_Threads, Test_Addition_3) {
    const int nthreads = std::thread::hardware_concurrency() * 13;
    std::vector<int> vector = getrandvect(nthreads);
    int serial_add = getserialOps(vector, "+");
    int approp_add = getappropOps(vector, "+");
    ASSERT_EQ(serial_add, approp_add);
}

TEST(Parallel_Operations_Std_Threads, Test_Difference) {
    const int nthreads = std::thread::hardware_concurrency() * 14;
    std::vector<int> vector = getrandvect(nthreads);
    int serial_difference = getserialOps(vector, "-");
    int approp_difference = getappropOps(vector, "-");
    ASSERT_EQ(serial_difference, approp_difference);
}

TEST(Parallel_Operations_Std_Threads, Test_Difference_2) {
    const int nthreads = std::thread::hardware_concurrency() * 15;
    std::vector<int> vector = getrandvect(nthreads);
    int serial_difference = getserialOps(vector, "-");
    int approp_difference = getappropOps(vector, "-");
    ASSERT_EQ(serial_difference, approp_difference);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
