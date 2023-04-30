// Copyright 2023 Mikerin Ilya
#include <gtest/gtest.h>
#include <vector>
#include "./ShellSortOmp.h"


TEST(Omp_Merge, Test_Merge_Sort) {
    std::vector<double> vec = {1, 4, 6, 3, 5, 2};
    std::vector<double> result = {1, 2, 3, 4, 5, 6};

    MergeSortOmp(vec, 0, vec.size()-1);

    ASSERT_EQ(vec, result);
}

TEST(Omp_Merge, Test_Merge_Sort_rand) {
    std::vector<double> vec = getRandomVector(100000);
    std::vector<double> vec1 = std::vector<double >(vec);
    bool nice = true;
    double t1 = 0, t2 = 0;
    double seqt = 0, ompt = 0;

    t1 = omp_get_wtime();
    MergeSort(vec, 0, vec.size()-1);
    t2 = omp_get_wtime();
    seqt = t2-t1;
    std::cout << "seqtime: " << seqt << std::endl;

    t1 = omp_get_wtime();
    MergeSortOmp(vec1, 0, vec1.size()-1);
    t2 = omp_get_wtime();
    ompt = t2-t1;

    std::cout << "omptime: " << ompt << std::endl;



    for (int i =0; i< vec.size()-1; i++) {
        if ( vec.at(i) > vec.at(i+1) ) nice = false;
    }

    ASSERT_TRUE(nice);
    ASSERT_TRUE(ompt < seqt);
}

TEST(Omp_Shell, Test_Shell_Sort) {
    std::vector<double> vec = {1, 4, 6, 3, 5, 2};
    std::vector<double> result = {1, 2, 3, 4, 5, 6};

    ShellSortOmp(vec);

    ASSERT_EQ(vec, result);
}

TEST(Omp_Shell, Test_Shell_Sort_Empty) {
    std::vector<double> vec = {};
    std::vector<double> result = {};

    ShellSortOmp(vec);

    ASSERT_EQ(vec, result);
}

TEST(Omp_Shell, Test_Shell_Sort_rand) {
    std::vector<double> vec = getRandomVector(100000);
    std::vector<double> vec1 = std::vector<double >(vec);
    bool nice = true;
    double t1 = 0, t2 = 0;
    double seqt = 0, ompt = 0;

    t1 = omp_get_wtime();
    ShellSort(vec);
    t2 = omp_get_wtime();
    seqt = t2-t1;
    std::cout << "seqtime: " << seqt << std::endl;

    t1 = omp_get_wtime();
    ShellSortOmp(vec1);
    t2 = omp_get_wtime();
    ompt = t2-t1;

    std::cout << "omptime: " << ompt << std::endl;



    for (int i =0; i< vec.size()-1; i++) {
        if ( vec.at(i) > vec.at(i+1) ) nice = false;
    }

    ASSERT_TRUE(nice);
    ASSERT_TRUE(ompt < seqt);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
