// Copyright 2023 Tsvetkov
#include "../../../modules/task_1/tsvetkov_a_hoara_and_betcher/hoara_and_betcher.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>


void GetMas(int* a, int n) {
    // a = new int[n];
    std::default_random_engine rnd{std::random_device { } ()};
    std::uniform_int_distribution<> dist(0, 100);
    for (int i = 0; i < n; i++) {
        a[i] = dist(rnd);
    }
}

void HoaraSort(int* a, int start, int finish) {
    int mid = a[(start + finish) / 2];
    int tmp;
    int l = start;
    int r = finish;
    while (l   <= r) {
        while (a[l] < mid)
            l++;
        while (a[r] > mid)
            r--;

            if (l < r) {
                tmp = a[l];
                a[l] = a[r];
                a[r] = tmp;
            }
            if (l <= r) {
                l++;
                r--;
            }
    }
    if (r > start)
        HoaraSort(a, start, r);
    if (l < finish)
        HoaraSort(a, l, finish);
}
void PerfectUnshuffle(int a[], int b[], int size1, int size2, int* res) {
    int i1, i2, k = 0;
    for (i1 = 0, i2 = 0; i1 < size1 && i2 < size2; ) {
        if (a[i1] <= b[i2]) {
            res[k] = a[i1];
            i1 += 2;
        } else {
            res[k] = b[i2];
            i2 += 2;
        }
        k++;
    }
    if (i1 >= size1) {
        for (int l = i2; l < size2; l += 2) {
            res[k] = b[l];
            k++;
        }
    } else {
        for (int l = i1; l < size1; l += 2) {
            res[k] = a[l];
            k++;
        }
    }
    for (i1 = 1, i2 = 1; i1 < size1 && i2 < size2;) {
        if (a[i1] <= b[i2]) {
            res[k] = a[i1];
            i1 += 2;
        } else {
            res[k] = b[i2];
            i2 += 2;
        }
        k++;
    }
    if (i1 >= size1) {
        for (int l = i2; l < size2; l += 2) {
            res[k] = b[l];
            k++;
        }
    } else {
        for (int l = i1; l < size1; l += 2) {
            res[k] = a[l];
            k++;
        }
    }
}
void PerfectShuffle(int* res, int size) {
    int k = size / 2;
    int buf;
    int i, j;
    double* tmp = new double[size];
    for (i = 0, j = 0; i < size; i += 2, j++) {
        tmp[i] = res[j];
        tmp[i + 1] = res[k+j];
    }
    for (i = 0; i < size; i++) {
        res[i] = tmp[i];
    }
    delete[] tmp;
    for (int i = 1; i < size; i++) {
        if (res[i] < res[i - 1]) {
            buf = res[i - 1];
            res[i - 1] = res[i];
            res[i] = buf;
        }
    }
}
void BetcherSort(int a[], int b[], int size1, int size2, int* res) {
    int newsize = size1 + size2;
    PerfectUnshuffle(a, b, size1, size2, res);
    PerfectShuffle(res, newsize);
}





