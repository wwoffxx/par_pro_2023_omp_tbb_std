// Copyright 2023 Mokrousov Artem
#include "./crs_mult_matrix_tbb.h"

TEST(TBB_CRSMatrix, CreateZeroMat) { EXPECT_NO_THROW(zerpMatrix(13, 13)); }

TEST(TBB_CRSMatrix, CreateRandomMat) {
    EXPECT_NO_THROW(genMatrix(13, 13, 0.5));
}

TEST(TBB_CRSMatrix, CreateRandomMatDensityNotCorrect_1) {
    EXPECT_ANY_THROW(genMatrix(13, 13, 2));
}

TEST(TBB_CRSMatrix, CreateRandomMatDensityNotCorrect_2) {
    EXPECT_ANY_THROW(genMatrix(13, 13, -1));
}

TEST(TBB_CRSMatrix, MatrixMult_1) {
    std::vector<std::vector<double>> v1 = {{0, 3}, {0, 7}};
    std::vector<std::vector<double>> v2 = {{1, 0}, {0, 1}};
    EXPECT_EQ(mulMatrix(v1, v2), v1);
}

TEST(TBB_CRSMatrix, MatrixMult_2) {
    std::vector<std::vector<double>> v1 = {{0, 3}, {0, 7}};
    std::vector<std::vector<double>> v2 = {{1, 1}, {0, 1}};
    std::vector<std::vector<double>> v3 = {{0, 3}, {0, 7}};
    EXPECT_EQ(mulMatrix(v1, v2), v3);
}

TEST(TBB_CRSMatrix, CreateCRSMatrix) {
    std::vector<std::vector<double>> v1 = {{0, 3}, {0, 7}};
    EXPECT_NO_THROW(CRSMatrix crs(v1));
}

TEST(TBB_CRSMatrix, TransposeCRS) {
    std::vector<double> v1 = {0, 10, 0, 10, 0};
    std::vector<double> v2 = {0, 0, 21, 0, 1};
    std::vector<double> v3 = {0, 0, 0, 0, 0};
    std::vector<double> v4 = {3, 0, 0, 0, 25};
    std::vector<double> v1T = {0, 0, 0, 3};
    std::vector<double> v2T = {10, 0, 0, 0};
    std::vector<double> v3T = {0, 21, 0, 0};
    std::vector<double> v4T = {10, 0, 0, 0};
    std::vector<double> v5T = {0, 1, 0, 25};
    std::vector<std::vector<double>> v = {v1, v2, v3, v4};
    std::vector<std::vector<double>> vT = {v1T, v2T, v3T, v4T, v5T};
    EXPECT_EQ(CRSMatrix(v), CRSMatrix(vT).T());
}

TEST(TBB_CRSMatrix, MultCRS) {
    std::vector<std::vector<double>> v1 = genMatrix(3, 3, 0.5);
    std::vector<std::vector<double>> v2 = genMatrix(3, 3, 0.5);
    CRSMatrix crs1(v1);
    CRSMatrix crs2(v2);
    EXPECT_EQ(crs1.dot(crs2.T()), CRSMatrix(mulMatrix(v1, v2)));
}

TEST(TBB_CRSMatrix, CRSTBBMult) {
    std::vector<std::vector<double>> v1 = genMatrix(3, 3, 0.5);
    std::vector<std::vector<double>> v2 = genMatrix(3, 3, 0.5);
    CRSMatrix crs1(v1);
    CRSMatrix crs2(v2);
    EXPECT_EQ(crs1.tbbDot(crs2.T()), CRSMatrix(mulMatrix(v1, v2)));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
