// Copyright 2023 Korobeynikova Alice
#pragma once
#include <vector>

typedef unsigned char Color;
typedef std::vector<Color> Image;

void linearHistogramStretching(Color* image, const int size);
void linearHistogramStretchingParallel(Color* image, const int size);
