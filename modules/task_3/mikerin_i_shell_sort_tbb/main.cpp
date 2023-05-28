// Copyright 2023 Mikerin Ilya
#include <gtest/gtest.h>
#include <vector>
#include "ShellSort.h"


TEST(TBB_Merge, Test_Merge_Sort) {
    std::vector<double> vec = {1, 4, 6, 3, 5, 2};
    std::vector<double> result = {1, 2, 3, 4, 5, 6};

    MergeSortTBB(vec, 0, vec.size()-1);

    ASSERT_EQ(vec, result);
}

TEST(TBB_Merge, Test_Merge_Sort_rand) {
    std::vector<double> vec = getRandomVector(10000000);
std::vector<double> Copyvec = std::vector<double >(vec);
    bool nice = true;

tbb::tick_count begin = tbb::tick_count::now();
MergeSort(Copyvec, 0, Copyvec.size()-1);

tbb::tick_count end = tbb::tick_count::now();
std::cout << "Seq TIME " << (end - begin).seconds() << std::endl;



    begin = tbb::tick_count::now();
    MergeSortTBB(vec, 0, vec.size()-1);

    end = tbb::tick_count::now();
    std::cout << "PARALLEL TIME " << (end - begin).seconds() << std::endl;



for (int i =0; i< vec.size()-1; i++) {
        if ( vec.at(i) > vec.at(i+1) ) nice = false;
    }

    ASSERT_TRUE(nice);
}

TEST(TBB_Shell, Test_Shell_Sort) {
    std::vector<double> vec = {1, 4, 6, 3, 5, 2};
    std::vector<double> result = {1, 2, 3, 4, 5, 6};

    ShellSortTBB(vec);

    ASSERT_EQ(vec, result);
}

TEST(TBB_Shell, Test_Shell_Sort_Empty) {
    std::vector<double> vec = {};
    std::vector<double> result = {};

    ShellSort(vec);


    ASSERT_EQ(vec, result);
}

TEST(TBB_Shell, Test_Shell_Sort_rand) {
    bool nice = true;

    std::vector<double> vec = getRandomVector(1000000);
    std::vector<double> Copyvec = std::vector<double>(vec);


tbb::tick_count begin = tbb::tick_count::now();
ShellSort(Copyvec);

tbb::tick_count end = tbb::tick_count::now();
std::cout << "Seq TIME " << (end - begin).seconds() << std::endl;



begin = tbb::tick_count::now();
ShellSortTBB(vec);

end = tbb::tick_count::now();
std::cout << "PARALLEL TIME " << (end - begin).seconds() << std::endl;

    for (int i =0; i< vec.size()-1; i++) {
        if (vec.at(i) > vec.at(i+1)) nice = false;
    }

    ASSERT_TRUE(nice);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
