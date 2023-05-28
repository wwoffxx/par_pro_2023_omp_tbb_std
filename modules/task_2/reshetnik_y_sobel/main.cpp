// Copyright 2023 Reshetnik Yana
#include "./sobel.h"

TEST(OmpSobel, WidthIncorrect) { EXPECT_ANY_THROW(getRandomImage(0, 1)); }

TEST(OmpSobel, HeightIncorrect) { EXPECT_ANY_THROW(getRandomImage(1, 0)); }

TEST(OmpSobel, SizeIsIncorrect) { EXPECT_ANY_THROW(getRandomImage(0, 0)); }

TEST(OmpSobel, SizeIsCorrect) { EXPECT_NO_THROW(getRandomImage(1, 1)); }

TEST(OmpSobel, WidthIsEqual) {
    Image img(32, 32);
    ASSERT_EQ(img.width, 32);
}

TEST(OmpSobel, HeightIsEqual) {
    Image img(32, 32);
    ASSERT_EQ(img.height, 32);
}
