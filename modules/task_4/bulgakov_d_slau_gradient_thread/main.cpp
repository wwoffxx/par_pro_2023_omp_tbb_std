// Copyright 2023 Bulgakov Daniil


#include <gtest/gtest.h>

#include "../../../modules/task_4/bulgakov_d_slau_gradient_thread/slau_gradient.h"


const double SML = 1.0e-4;

void GoogleAssertNear(dvec a, dvec b, double smol) {
    ASSERT_EQ(a.size(), b.size()) << "Vectors sizes not equal";
    for (size_t i = 0; i < a.size(); i++) {
        ASSERT_NEAR(a[i], b[i], smol) << "On index [" << i << "]";
    }
}

TEST(Sequential, Test_1) {
    dmat A =  generateMatrix(10, 423);
    dvec ans = generateVector(10, 234);
    dvec B = matrix_vec(A, ans);
    dvec std_solved = std_solve(A, B);
    dvec solved = solve(A, B);
    GoogleAssertNear(std_solved, solved, SML);
}

TEST(Sequential, Test_2) {
    dmat A =  generateMatrix(50, 243);
    dvec ans = generateVector(50, 423);
    dvec B = matrix_vec(A, ans);
    dvec std_solved = std_solve(A, B);
    dvec solved = solve(A, B);
    GoogleAssertNear(std_solved, solved, SML);
}

TEST(Sequential, Test_3) {
    dmat A =  generateMatrix(100, 4442);
    dvec ans = generateVector(100, 2444);
    dvec B = matrix_vec(A, ans);
    dvec std_solved = std_solve(A, B);
    dvec solved = solve(A, B);
    GoogleAssertNear(std_solved, solved, SML);
}

TEST(Sequential, Test_4) {
    dmat A =  generateMatrix(200, 15);
    dvec ans = generateVector(200, 51);
    dvec B = matrix_vec(A, ans);
    dvec std_solved = std_solve(A, B);
    dvec solved = solve(A, B);
    GoogleAssertNear(std_solved, solved, SML);
}

TEST(Sequential, Test_5) {
    dmat A =  generateMatrix(500, 155);
    dvec ans = generateVector(500, 551);
    dvec B = matrix_vec(A, ans);
    dvec std_solved = std_solve(A, B);
    dvec solved = solve(A, B);
    GoogleAssertNear(std_solved, solved, SML);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
