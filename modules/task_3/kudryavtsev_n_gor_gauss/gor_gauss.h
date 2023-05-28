// Copyright 2023 Kudryavtsev Nikita
#ifndef MODULES_TASK_3_KUDRYAVTSEV_N_GOR_GAUSS_GOR_GAUSS_H_
#define MODULES_TASK_3_KUDRYAVTSEV_N_GOR_GAUSS_GOR_GAUSS_H_

#pragma once

#include <tbb/parallel_for.h>
#include <vector>
#include <cstdint>

constexpr uint32_t kernelSize = 3;

std::vector<float> getKernel(uint32_t n);

void hexToColors(uint32_t hex, uint8_t *red, uint8_t *green, uint8_t *blue);

uint32_t colorsToHex(uint8_t red, uint8_t green, uint8_t blue);

template<typename T>
T clamp(T value, T min, T max);

uint32_t getColor(const std::vector<uint32_t> &image, uint32_t width, uint32_t height, uint32_t x, uint32_t y);

std::vector<uint32_t> processLine(
    const std::vector<uint32_t> &image,
    uint32_t width,
    uint32_t height,
    uint32_t lineNumber
);
std::vector<uint32_t> process(const std::vector<uint32_t> &image, uint32_t width, uint32_t height);
std::vector<uint32_t> processParallel(const std::vector<uint32_t> &image, uint32_t width, uint32_t height);

#endif  // MODULES_TASK_3_KUDRYAVTSEV_N_GOR_GAUSS_GOR_GAUSS_H_
