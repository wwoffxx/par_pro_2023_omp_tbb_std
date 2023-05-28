// Copyright 2023 Bulgakov Daniil

#include <gtest/gtest.h>

#include "../../../modules/task_1/bulgakov_d_slau_gradient/slau_gradient.h"


const double SML = 1.0e-4;

void GoogleAssertNear(dvec a, dvec b, double smol) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            ASSERT_NEAR(a[i], b[i], smol);
        }
    }
}

TEST(Sequential, Test_1) {
    dmat A =  generateMatrix(2, 423);
    dvec ans = generateVector(2, 234);
    dvec B = matrix_vec(A, ans);
    dvec solved = solve(A, B);
    GoogleAssertNear(solved, ans, SML);
}

TEST(Sequential, Test_2) {
    dmat A =  generateMatrix(5, 243);
    dvec ans = generateVector(5, 423);
    dvec B = matrix_vec(A, ans);
    dvec solved = solve(A, B);
    GoogleAssertNear(solved, ans, SML);
}

TEST(Sequential, Test_3) {
    dmat A =  generateMatrix(7, 4442);
    dvec ans = generateVector(7, 2444);
    dvec B = matrix_vec(A, ans);
    dvec solved = solve(A, B);
    GoogleAssertNear(solved, ans, SML);
}

TEST(Sequential, Test_4) {
    dmat A =  generateMatrix(10, 15);
    dvec ans = generateVector(10, 51);
    dvec B = matrix_vec(A, ans);
    dvec solved = solve(A, B);
    GoogleAssertNear(solved, ans, SML);
}

TEST(Sequential, Test_5) {
    dmat A =  generateMatrix(100, 155);
    dvec ans = generateVector(100, 551);
    dvec B = matrix_vec(A, ans);
    dvec solved = solve(A, B);
    GoogleAssertNear(solved, ans, SML);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



