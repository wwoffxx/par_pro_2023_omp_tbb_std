// Copyright 2023 Rezchikov Dmitrii
#include <gtest/gtest.h>
#include "../../../modules/task_2/rezchikov_d_radix_simple_omp/ops.h"


TEST(OMP, Test_Size_0) {
    std::vector<int> v{};
    std::vector<int> ref{};
    v = radSortParMerge(&v);
    ASSERT_EQ(v, ref);
}

TEST(OMP, Test_Size_1) {
    std::vector<int> v{1};
    std::vector<int> ref{1};
    radSortParMerge(&v);
    ASSERT_EQ(v, ref);
}

TEST(OMP, Test_Size_100) {
    const int N = 100;
    auto vec = getRndVector(N);
    auto ref = std::vector<int>(vec);
    std::stable_sort(ref.begin(), ref.end());
    radSortParMerge(&vec);

    ASSERT_EQ(vec, ref);
}

TEST(OMP, Test_Size_1000) {
    const int N = 1000;
    auto vec = getRndVector(N);
    auto ref = std::vector<int>(vec);
    std::stable_sort(ref.begin(), ref.end());
    radSortParMerge(&vec);

    ASSERT_EQ(vec, ref);
}

TEST(OMP, Test_Size_100000) {
    const int N = 100000;
    auto vec = getRndVector(N);
    auto ref = std::vector<int>(vec);
    std::stable_sort(ref.begin(), ref.end());
    radSortParMerge(&vec);

    ASSERT_EQ(vec, ref);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
