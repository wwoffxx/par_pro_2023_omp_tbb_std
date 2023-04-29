// Copyright 2023 Sukharev Artem
#include <gtest/gtest.h>
#include <omp.h>
#include <vector>
#include "../../../modules/task_2/sukharev_a_convex_hull_binimg_omp/convex_hull_binimg.h"

TEST(Parallel_Operations_OpenMP, Test_Full_Square) {
    std::vector<std::vector<int>> g = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };
    std::vector<std::vector<int>> expRes = {
        {1, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 1}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}

TEST(Parallel_Operations_OpenMP, Test_Empty_Img) {
    std::vector<std::vector<int>> g = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> expRes = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}


TEST(Parallel_Operations_OpenMP, Test_One_Line_Component) {
    std::vector<std::vector<int>> g = {
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> expRes = {
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}

TEST(Parallel_Operations_OpenMP, Test_Comp_In_Corners) {
    std::vector<std::vector<int>> g = {
        {1, 1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 1, 0},
        {1, 1, 1, 1, 0, 1, 1, 1}
    };
    std::vector<std::vector<int>> expRes = {
        {1, 1, 0, 0, 0, 0, 0, 2},
        {1, 0, 1, 0, 0, 0, 2, 0},
        {0, 0, 1, 0, 0, 0, 2, 2},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 3, 3, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 4, 0},
        {3, 0, 0, 3, 0, 4, 0, 4}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}

TEST(Parallel_Operations_OpenMP, Test_Some_Diffrent_Components) {
    std::vector<std::vector<int>> g = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> expRes = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 2, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 3},
        {0, 0, 3, 0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}

TEST(Parallel_Operations_OpenMP, Test_Nested_Components) {
    std::vector<std::vector<int>> g = {
        {0, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 1, 0, 0},
        {1, 0, 1, 1, 0, 0, 0, 1, 0},
        {1, 0, 0, 1, 1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0}
    };
    std::vector<std::vector<int>> expRes = {
        {0, 1, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 2, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0}
    };
    std::vector<std::vector<int>> res = build_convhull_img(g);
    ASSERT_EQ(res, expRes);
}

// TEST(Parallel_Operations_OpenMP, Test_Time) {
//    int n = 4002;
//    std::vector<std::vector<int>> g(n, std::vector<int>(n, 0));
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            if ((i + j) / 5 % 3 == 0) {
//                g[i][j] = 1;
//            }
//        }
//    }
//    double t1 = 0, t2 = 0;
//    t1 = omp_get_wtime();
//    std::vector<std::vector<int>> res1 = build_convhull_img(g);
//    t1 = omp_get_wtime()-t1;
//    t2 = omp_get_wtime();
//    std::vector<std::vector<int>> res2 = build_convhull_img(g, false);
//    t2 = omp_get_wtime()-t2;
//    std::cout << t1 << " " << t2 << std::endl;
//    ASSERT_EQ(res1, res2);
// }


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
