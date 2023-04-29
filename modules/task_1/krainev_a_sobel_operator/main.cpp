// Copyright 2023 Krainev Alexander
#include <gtest/gtest.h>
#include "./sobel_operator.h"

TEST(Seq_Sobel, Empty_Image) {
    const Image image = white_image(15, 15);
    const Image excected = black_image(15, 15);
    const Image result = sobel(image);
    ASSERT_EQ(true, true);
}

TEST(Seq_Sobel, Image_3x3_Mono) {
    Image image = {
        { {255, 255, 0}, {255, 255, 0}, {255, 255, 0} },
        { {255, 255, 0}, {255, 255, 0}, {255, 255, 0} },
        { {255, 255, 0}, {255, 255, 0}, {255, 255, 0} }
    };
    Image expected = black_image(3, 3);

    const Image result = sobel(image);
    ASSERT_EQ(expected, result);
}

TEST(Seq_Sobel, Image_3x3_Duo) {
    Image image = {
        { {255, 255, 0}, {255, 255, 0}, {0, 0, 255} },
        { {255, 255, 0}, {255, 255, 0}, {0, 0, 255} },
        { {0, 0, 255}, {0, 0, 255}, {0, 0, 255} }
    };
    Image expected = {
        {{0, 0, 0}, {255, 255, 255}, {255, 255, 255} },
        { {255, 255, 255}, {255, 255, 255}, {255, 255, 255} },
        { {255, 255, 255}, {255, 255, 255}, {255, 255, 255}}
    };
    const Image result = sobel(image);
    ASSERT_EQ(expected, result);
}

TEST(Seq_Sobel, Image_3x3_Triple) {
    Image image = {
        { {0, 255, 0}, {0, 255, 0}, {255, 0, 0} },
        { {255, 0, 0}, {255, 0, 0}, {0, 0, 255} },
        { {255, 0, 0}, {255, 0, 0}, {0, 0, 255} }
    };
    Image expected = {
        { {255, 255, 0}, {255, 255, 255}, {255, 255, 255} },
        { {255, 255, 0}, {255, 255, 255}, {255, 255, 255} },
        { {0, 0, 0}, {255, 0, 255}, {255, 0, 255} }
    };
    const Image result = sobel(image);
    ASSERT_EQ(expected, result);
}

TEST(Seq_Sobel, Image_2x5) {
    Image image = {
        { {210, 100, 15}, {200, 117, 120} },
        { {234, 112, 84}, {37, 75, 24} },
        { {100, 42, 50}, {39, 55, 13} },
        { {0, 0, 0}, {255, 0, 255} },
        { {190, 0, 240}, {255, 10, 181} }
    };
    Image expected = {
        { {244, 15, 255}, {255, 114, 255} },
        { {255, 240, 52}, {255, 247, 255} },
        { {255, 255, 122}, {255, 255, 255} },
        { {255, 172, 255}, {255, 178, 255} },
        { {255, 31, 255}, {255, 42, 80} }
    };
    const Image result = sobel(image);
    ASSERT_EQ(expected, result);
}

TEST(Seq_Sobel, Image_1x5) {
    Image image = {
        { {110, 200, 115} },
        { {134, 12, 83} },
        { {21, 42, 250} },
        { {52, 71, 58} },
        { {99, 90, 40} }
    };
    Image expected = {
        { {96, 255, 128} },
        { {255, 255, 255} },
        { {255, 236, 100} },
        { {255, 192, 255} },
        { {188, 76, 72} }
    };
    const Image result = sobel(image);
    ASSERT_EQ(expected, result);
}
