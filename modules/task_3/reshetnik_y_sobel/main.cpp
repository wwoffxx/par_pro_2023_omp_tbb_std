// Copyright 2023 Reshetnik Yana
#include "./sobel.h"

void RunTest(int w, int h) {
    std::vector<int> SourceImg = CreateRandomImage(w, h);
    std::vector<int> ResSeq = SequentialSobelFilter(SourceImg, w, h);
    std::vector<int> ResPar = ParallelSobelFilter(SourceImg, w, h);
    EXPECT_EQ(ResSeq, ResPar);
}

TEST(TBBSobel, Test_3x3) { RunTest(3, 3); }

TEST(TBBSobel, Test_10x10) { RunTest(10, 10); }

TEST(TBBSobel, Test_15x20) { RunTest(10, 10); }

TEST(TBBSobel, Test_30x50) { RunTest(30, 50); }

TEST(TBBSobel, Test_100x150) { RunTest(100, 150); }

/* TEST(TBBSobel, Test_1600x500) {
    int w = 1600, h = 500;
    std::vector<int> SourceImg = CreateRandomImage(w, h);

    tbb::tick_count start = tbb::tick_count::now();
    std::vector<int> ResSeq = SequentialSobelFilter(SourceImg, w, h);
    tbb::tick_count finish = tbb::tick_count::now();

    auto timeSeq = (finish - start).seconds();

    start = tbb::tick_count::now();
    std::vector<int> ResPar = ParallelSobelFilter(SourceImg, w, h);
    finish = tbb::tick_count::now();

    auto timePar = (finish - start).seconds();

    std::cout << "Seq:          " << timeSeq << "\n";
    std::cout << "TBB Parallel: " << timePar << '\n';
    EXPECT_EQ(ResSeq, ResPar);
} */

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
