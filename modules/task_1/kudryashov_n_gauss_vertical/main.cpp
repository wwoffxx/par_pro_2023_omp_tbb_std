  // Copyright 2023 Kudryashov Nikita
#include <gtest/gtest.h>
#include <vector>
#include "./kudryashov_n_gauss_vertical.h"

TEST(gauss_vertical, test_image_3x3) {
    int height = 3;
    int width = 3;
    std::vector<std::vector<int>> img = { {123, 226, 1},
                                          {181, 143, 223},
                                          {243, 83, 196} };
    std::vector<std::vector<int>> expectedImg = { {145, 169, 66},
                                              {175, 158, 175},
                                              {209, 134 , 182} };
    std::vector<std::vector<int>> resultImg = gauss_filter_sequence(
        img, height, width);
    ASSERT_EQ(expectedImg, resultImg);
}

TEST(gauss_vertical, test_image_4x4) {
    int height = 4;
    int width = 4;
    std::vector<std::vector<int>> img = { {234, 125, 174, 146},
                                          {238, 146, 158, 138},
                                          {220, 225, 92, 132},
                                          {135, 161, 37, 233} };
    std::vector<std::vector<int>> expectedImg = { {217, 153, 159, 149},
                                          {221, 167, 148, 140},
                                          {207, 184, 121, 140},
                                          {152, 147, 95, 187} };
    std::vector<std::vector<int>> resultImg = gauss_filter_sequence(
        img, height, width);
    ASSERT_EQ(expectedImg, resultImg);
}

TEST(gauss_vertical, test_image_5x5) {
    int height = 5;
    int width = 5;
    std::vector<std::vector<int>> img = { {203, 78, 115, 27, 90},
                                          {7, 206, 96, 22, 169},
                                          {28, 141, 106, 21, 255},
                                          {202, 197, 97, 250, 168},
                                          {161, 108, 118, 90, 190} };
    std::vector<std::vector<int>> expectedImg = { {158, 113, 95, 53, 90},
                                          {64, 139, 99, 60, 145},
                                          {71, 133, 105, 94, 198},
                                          {167, 159, 127, 171, 185},
                                          {160, 128, 116, 127, 174} };
    std::vector<std::vector<int>> resultImg = gauss_filter_sequence(
        img, height, width);
    ASSERT_EQ(expectedImg, resultImg);
}

TEST(gauss_vertical, test_image_6x4) {
    int height = 6;
    int width = 4;
    std::vector<std::vector<int>> img = { {142, 202, 45, 115},
                                          {1, 47, 224, 162},
                                          {87, 37, 4, 253},
                                          {95, 92, 29, 67},
                                          {186, 241, 52, 83},
                                          {13, 67, 115, 123} };
    std::vector<std::vector<int>> expectedImg = { {128, 149, 99, 114},
                                          {44, 80, 145, 167},
                                          {69, 51, 72, 179},
                                          {108, 94, 53, 88},
                                          {149, 158, 84, 82},
                                          {50, 88, 105, 114} };
    std::vector<std::vector<int>> resultImg = gauss_filter_sequence(
        img, height, width);
    ASSERT_EQ(expectedImg, resultImg);
}

TEST(gauss_vertical, test_image_4x6) {
    int height = 4;
    int width = 6;
    std::vector<std::vector<int>> img = { {183, 16, 27, 224, 130, 217},
                                          {227, 108, 222, 164, 102, 143},
                                          {103, 125, 90, 198, 0, 49},
                                          {23, 254, 17, 221, 150, 84} };
    std::vector<std::vector<int>> expectedImg = { {163, 62, 80, 173, 153, 191},
                                          {181, 124, 157, 162, 112, 131},
                                          {115, 130, 123, 154, 72, 65},
                                          {68, 166, 94, 170, 132, 85} };
    std::vector<std::vector<int>> resultImg = gauss_filter_sequence(
        img, height, width);
    ASSERT_EQ(expectedImg, resultImg);
}
