// Copyright 2023 Busko Polina
#include <gtest/gtest.h>
#include "./operator_sobelya.h"
TEST(createImg, one) {
    ASSERT_ANY_THROW(Img I(-2, 1));
}
TEST(createImg, two) {
    ASSERT_ANY_THROW(Img I(10, -1, 7));
}
TEST(createImg, three) {
    ASSERT_NO_THROW(Img I(10, 10, 7));
}
TEST(SobelFilter, matrix_1_on_1) {
    std::vector<std::vector<int>> anser = { {0} };
    Img I(1, 1, 0);
    std::vector<std::vector<int>> res = I.SeqSobel();
    ASSERT_EQ(anser, res);
}
TEST(SobelFilter, matrix_5_on_5) {
    std::vector<std::vector<int>> anser =
                        { {1, 1, 1, 1, 1},
                          {1, 0, 0, 0, 1},
                          {1, 0, 0, 0, 1},
                          {1, 0, 0, 0, 1},
                          {1, 1, 1, 1, 1} };
    Img I(5, 5, 1);
    std::vector<std::vector<int>> res = I.SeqSobel();
    EXPECT_EQ(anser, res);
}
TEST(SobelFilter, randomMatrix_10_on_10) {
    int size = 10;
    Img imgTest2(size, size);
    // imgTest2.print();
    std::cout << std::endl;
    std::vector<std::vector<int>> testS2 = imgTest2.SeqSobel();
    /*for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << testS2[i][j] << " ";
        }
        std::cout << std::endl;
    }*/
    ASSERT_TRUE(true);
}
TEST(SobelFilter, randomMatrix_100_on_100) {
    int size = 100;
    Img imgTest2(size, size);
    // imgTest2.print();
    std::cout << std::endl;
    std::vector<std::vector<int>> testS2 = imgTest2.SeqSobel();
    /*for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << testS2[i][j] << " ";
        }
        std::cout << std::endl;
    }*/
    ASSERT_TRUE(true);
}
/*TEST(SobelFilter, randomMatrix_10000_on_10000) {
    int size = 10000;
    Img imgTest2(size, size);
    std::cout << std::endl;
    std::vector<std::vector<int>> testS2 = imgTest2.SeqSobel();
    ASSERT_TRUE(true);
}*/
