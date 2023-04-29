// Copyright 2023 Simeunovic Aleksandar
#include <gtest/gtest.h>
#include <omp.h>
#include "./gauss_horizontal_filter.h"
#define THREAD_NUM 4

TEST(Gauss_Filter, _50x50) {
    int width = 50;
    int height = 50;
    std::vector<uint8_t> img = GetRandMatrix(width, height);
    std::vector<uint8_t> seq;
    std::vector<uint8_t> par;

    seq = Filter(img, width, height, 32);
    par = ParFilter(img, width, height, THREAD_NUM, 32);
    ASSERT_EQ(seq, par);
}

TEST(Gauss_Filter, _100x100) {
    int width = 100;
    int height = 100;
    std::vector<uint8_t> img = GetRandMatrix(width, height);
    std::vector<uint8_t> seq;
    std::vector<uint8_t> par;

    seq = Filter(img, width, height, 32);
    par = ParFilter(img, width, height, THREAD_NUM, 32);
    ASSERT_EQ(seq, par);
}

TEST(Gauss_Filter, _200x200) {
    int width = 200;
    int height = 200;
    std::vector<uint8_t> img = GetRandMatrix(width, height);
    std::vector<uint8_t> seq;
    std::vector<uint8_t> par;

    seq = Filter(img, width, height, 32);
    par = ParFilter(img, width, height, THREAD_NUM, 32);
    ASSERT_EQ(seq, par);
}

TEST(Gauss_Filter, _320x240) {
    int width = 320;
    int height = 240;
    std::vector<uint8_t> img = GetRandMatrix(width, height);
    std::vector<uint8_t> seq;
    std::vector<uint8_t> par;

    seq = Filter(img, width, height, 32);
    par = ParFilter(img, width, height, THREAD_NUM, 32);
    ASSERT_EQ(seq, par);
}

TEST(Gauss_Filter, _500x500) {
    int width = 500;
    int height = 500;
    std::vector<uint8_t> img = GetRandMatrix(width, height);
    std::vector<uint8_t> seq;
    std::vector<uint8_t> par;

    seq = Filter(img, width, height, 32);
    par = ParFilter(img, width, height, THREAD_NUM, 32);
    ASSERT_EQ(seq, par);
}