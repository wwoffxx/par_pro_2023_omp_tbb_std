// Copyright 2023 Dryamina Ksenia
#include <gtest/gtest.h>
#include <omp.h>
#include <algorithm>
#include <vector>
#include "./shell_sort.h"

TEST(Shell_Sort, Int_64) {
    int size = 8;
    std::vector<int> vec = genVector(size);

    std::vector<int> sequential = sequentialShellSort(vec);
    std::vector<int> parallel = parallelShellSort(vec);

    ASSERT_EQ(parallel, sequential);
}

TEST(Shell_Sort, Int_128) {
    int size = 128;
    std::vector<int> vec = genVector(size);

    std::vector<int> sequential = sequentialShellSort(vec);
    std::vector<int> parallel = parallelShellSort(vec);

    ASSERT_EQ(parallel, sequential);
}

TEST(Shell_Sort, Int_256) {
    int size = 256;
    std::vector<int> vec = genVector(size);

    std::vector<int> sequential = sequentialShellSort(vec);
    std::vector<int> parallel = parallelShellSort(vec);

    ASSERT_EQ(parallel, sequential);
}

TEST(Shell_Sort, Int_512) {
    int size = 512;
    std::vector<int> vec = genVector(size);

    std::vector<int> sequential = sequentialShellSort(vec);
    std::vector<int> parallel = parallelShellSort(vec);

    ASSERT_EQ(parallel, sequential);
}

TEST(Shell_Sort, Int_1024) {
    int size = 1024;
    std::vector<int> vec = genVector(size);

    std::vector<int> sequential = sequentialShellSort(vec);
    std::vector<int> parallel = parallelShellSort(vec);

    ASSERT_EQ(parallel, sequential);
}

/**
 * Efficiency test
 * Delete or comment when publishing to the main repository
 * Delete this commentary when publishing to the main repository
*/
// TEST(Shell_Sort, Time_Test) {
//     int size = 100000;
//     std::vector<int> vec = genVector(size);

//     double start = omp_get_wtime();
//     std::vector<int> sequential = sequentialShellSort(vec);
//     double end = omp_get_wtime();
//     std::cout << "Sequential: " << end - start << "\n";
//     start = omp_get_wtime();
//     std::vector<int> parallel = parallelShellSort(vec);
//     end = omp_get_wtime();
//     std::cout << "Parallel: " << end - start << "\n";

//     ASSERT_EQ(parallel, sequential);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
