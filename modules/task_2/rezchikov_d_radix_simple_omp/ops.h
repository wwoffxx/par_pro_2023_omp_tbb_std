// Copyright 2023 Rezchikov Dmitrii
#pragma once

#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <iostream>

void countingSortSeq(std::vector<int> * array, int l, int r, int place);
void countingSortPar(std::vector<int> * array, int l, int r, int place);
void radSortSeq(std::vector<int> * vec);
void radSortPar(std::vector<int> * vec);
std::vector<int> radSortParMerge(std::vector<int> * vec);
std::vector<int> getRndVector(int size);
std::vector<int> merge(std::vector<int> * v1, std::vector<int> * v2);
