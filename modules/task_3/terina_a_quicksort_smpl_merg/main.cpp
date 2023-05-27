// Copyright 2023 Terina Alina
#include <tbb/tbb.h>
#include <gtest/gtest.h>
#include <algorithm>

#include "../../../modules/task_3/terina_a_quicksort_smpl_merg/quicksort.h"

TEST(TBB_version_QS, can_sort_vec_100) {
    std::vector<int> our_vector = getRandomVector(100);
    ASSERT_NO_THROW(quicksort(&our_vector, 0, our_vector.size() - 1));
    EXPECT_TRUE(std::is_sorted(our_vector.begin(), our_vector.end()));
}

TEST(TBB_version_QS, can_sort_vec_1000) {
    std::vector<int> our_vector = getRandomVector(1000);
    int lastIndex = static_cast<int>(our_vector.size() - 1);
    ASSERT_NO_THROW(quicksort(&our_vector, 0, lastIndex));
    EXPECT_TRUE(std::is_sorted(our_vector.begin(), our_vector.end()));
}


TEST(TBB_version_QS, can_sort_vec_the_equal_sz) {
    std::vector<int> v1 = getRandomVector(50);
    std::vector<int> v2 = getRandomVector(50);
    quicksort(&v1, 0, v1.size() - 1);
    quicksort(&v2, 0, v2.size() - 1);
    std::vector<int> our_vector = merge(v1, v2);
    EXPECT_TRUE(std::is_sorted(our_vector.begin(), our_vector.end()));
}

TEST(TBB_version_QS, can_sort_vec_the_diff_sz) {
    std::vector<int> v1 = getRandomVector(50);
    std::vector<int> v2 = getRandomVector(24);
    quicksort(&v1, 0, v1.size() - 1);
    quicksort(&v2, 0, v2.size() - 1);
    std::vector<int> our_vector = merge(v1, v2);
    EXPECT_TRUE(std::is_sorted(our_vector.begin(), our_vector.end()));
}

TEST(TBB_version_QS, can_sort_vec_the_big_sz) {
    std::vector<int> v1 = getRandomVector(5000);
    std::vector<int> v2 = getRandomVector(5000);
    quicksort(&v1, 0, v1.size() - 1);
    quicksort(&v2, 0, v2.size() - 1);
    std::vector<int> our_vector = merge(v1, v2);
    EXPECT_TRUE(std::is_sorted(our_vector.begin(), our_vector.end()));
}


TEST(TBB_version_QS, can_sort_vec_and_comp_time) {
    std::vector<int> v1 = getRandomVector(1000000);

    tbb::tick_count t0 = tbb::tick_count::now();
    ASSERT_NO_THROW(_quickSort(&v1));
    tbb::tick_count t1 = tbb::tick_count::now();
    std::cout << "Tbb: " << (t1 - t0).seconds() << std::endl;

    std::vector<int> v2 = getRandomVector(1000000);

    tbb::tick_count t3 = tbb::tick_count::now();
    ASSERT_NO_THROW(quicksort(&v2, 0, v2.size() - 1));
    tbb::tick_count t4 = tbb::tick_count::now();
    std::cout << "smpl: " << (t4 - t3).seconds() << std::endl;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
