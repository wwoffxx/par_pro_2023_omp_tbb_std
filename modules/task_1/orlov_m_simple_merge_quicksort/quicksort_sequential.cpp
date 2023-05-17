// Copyright 2023 Maksim Orlov

#include <cstdlib>
#include "../../../modules/task_1/orlov_m_simple_merge_quicksort/quicksort_sequential.h"

void sw(double* a, double* b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

int quicksortPartition(double* arr, int start, int finish) {
    int pivot = finish - 1;
    int largeElem = start;
    for (int i = start; i < finish; i++) {
        if (arr[i] < arr[pivot]) {
            sw(arr + i, arr + largeElem);
            largeElem++;
        }
    }
    sw(arr + pivot, arr + largeElem);
    return largeElem;
}

void quicksortSequentialRecursive(double* arr, int start, int finish) {
    if (finish <= start + 1) return;
    int pivotPos = quicksortPartition(arr, start, finish);
    quicksortSequentialRecursive(arr, start, pivotPos);
    quicksortSequentialRecursive(arr, pivotPos + 1, finish);
}

void quicksortSequential(double* arr, int n) {
    if (n < 1) throw "Too few elements";
    quicksortSequentialRecursive(arr, 0, n);
}

bool compareArrays(double* a1, int n1, double* a2, int n2, double eps) {
    if (n1 != n2) return false;
    for (int i = 0; i < n1; i++) {
        if (std::abs(a1[i] - a2[i]) > eps) return false;
    }
    return true;
}
