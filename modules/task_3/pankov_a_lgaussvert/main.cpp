// Copyright 2023 Pankov Anatoliy
#include "./lgaussvert.h"

TEST(LGaussVerticalTBB, MatrixMN0Test) {
    int m = 0;
    int n = 0;
    std::vector<double> matrix(m * n);

    ASSERT_ANY_THROW(matrix = TBBGaussFilter(matrix, m, n));
}

TEST(LGaussVerticalTBB, ZeroMatrixTest3x3) {
    int m = 3;
    int n = 3;
    std::vector<double> matrix(0);

    ASSERT_ANY_THROW(matrix = TBBGaussFilter(matrix, m, n));
}

TEST(LGaussVerticalTBB, RandomTest3x3) {
    int m = 3;
    int n = 3;
    std::vector<double> matrix = MakeRandomMatrix(m, n);

    std::vector<double> SeqResult = SeqGaussFilter(matrix, n, m);
    std::vector<double> TBBResult = TBBGaussFilter(matrix, n, m);

    ASSERT_EQ(SeqResult, TBBResult);
}

TEST(LGaussVerticalTBB, RandomTest10x10) {
    int m = 10;
    int n = 10;
    std::vector<double> matrix = MakeRandomMatrix(m, n);

    std::vector<double> SeqResult = SeqGaussFilter(matrix, n, m);
    std::vector<double> TBBResult = TBBGaussFilter(matrix, n, m);

    ASSERT_EQ(SeqResult, TBBResult);
}

TEST(LGaussVerticalTBB, RandomTest50x50) {
    int m = 50;
    int n = 50;
    std::vector<double> matrix = MakeRandomMatrix(m, n);

    std::vector<double> SeqResult = SeqGaussFilter(matrix, n, m);
    std::vector<double> TBBResult = TBBGaussFilter(matrix, n, m);

    ASSERT_EQ(SeqResult, TBBResult);
}

/* TEST(LGaussVerticalTBB, RandomTest1000x1000) {
    int m = 1000;
    int n = 1000;
    std::vector<double> matrix = MakeRandomMatrix(m, n);

    tbb::tick_count seqStart = tbb::tick_count::now();
    std::vector <double> SeqResult = SeqGaussFilter(matrix, n, m);
    double seqTime = (tbb::tick_count::now() - seqStart).seconds();

    tbb::tick_count tbbStart = tbb::tick_count::now();
    std::vector <double> TBBResult = TBBGaussFilter(matrix, n, m);
    double tbbTime = (tbb::tick_count::now() - tbbStart).seconds();

    std::cout << "Sequential time: " << seqTime << std::endl;
    std::cout << "TBB time: " << tbbTime << std::endl;

    ASSERT_EQ(SeqResult, TBBResult);
} */

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
