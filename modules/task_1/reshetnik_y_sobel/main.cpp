// Copyright 2023 Reshetnik Yana
#include <gtest/gtest.h>
#include "./sobel.h"

TEST(SeqSobel, IndexCalcCorrect) {
    int x = 11, y = 13, w = 20;
    EXPECT_EQ(Index(x, y, w), 271);
}

TEST(SeqSobel, ClampMinIsCorrect) {
  EXPECT_EQ(Clamp(-1, 0, 255), 0);
}

TEST(SeqSobel, ClampMaxIsCorrect) {
  EXPECT_EQ(Clamp(256, 0, 255), 255);
}

TEST(SeqSobel, InitRandomMatrixThrows1) {
    ASSERT_ANY_THROW(InitRandomMatrix(0, 1));
}

TEST(SeqSobel, InitRandomMatrixThrows2) {
    ASSERT_ANY_THROW(InitRandomMatrix(1, 0));
}

TEST(SeqSobel, FilterCorrect) {
    std::vector<int> a = {44, 222, 87, 124,
                          0, 172, 218, 45,
                          87, 17, 116, 211,
                          118, 228, 74,  143 };
    int h = 4, w = 4;
    std::vector<int> result = XSobelFilter(a, h, w);
    std::vector<int> check = {255, 255, 0, 0,
                              255, 255, 0, 0,
                              142, 232, 176, 86,
                              255, 0, 0, 255};

    EXPECT_EQ(result, check);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
