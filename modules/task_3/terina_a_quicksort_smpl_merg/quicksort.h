// Copyright 2023 Terina Alina

#pragma once

#include <vector>

int separation(std::vector<int>* our_vector, int left , int right);
void quicksort(std::vector<int>* our_vector, int left, int right);
void quickSort(int l, int r, std::vector <double>* list);
std::vector<int> merge(const std::vector<int>& v1,
    const std::vector<int>& v2);
void genrndArr(double* arr, int n);
void _quickSort(std::vector<int>* our_vector);

std::vector<int> getRandomVector(int sz);

