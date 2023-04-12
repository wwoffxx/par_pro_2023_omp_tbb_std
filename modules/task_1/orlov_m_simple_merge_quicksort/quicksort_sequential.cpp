// Copyright 2023 Maksim Orlov

#include "quicksort_sequential.h"

void swap(double* a, double* b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

int quicksortPartition(double* arr, int start, int finish) {
    int pivot = finish - 1;
    int largeElem = start;
    for (int i = start; i < finish; i++) {
        if (arr[i] < arr[pivot]) {
            swap(arr + i, arr + largeElem);
            largeElem++;
        }
    }
    swap(arr + pivot, arr + largeElem);
    return largeElem;
}

void push(int* stack, int& size, int elem) {
    stack[size++] = elem;
}

int pop(int* stack, int& size) {
    return stack[--size];
}

void quicksortSequential(double* arr, int n) {
    int* stack = new int[n];
    int size = 0;
    int start, finish, pivotPos;

    push(stack, size, 0);
    push(stack, size, n);
    while (size > 0) {
        finish = pop(stack, size);
        start = pop(stack, size);
        pivotPos = quicksortPartition(arr, start, finish);
        if (finish - pivotPos > 1) {
            push(stack, size, pivotPos);
            push(stack, size, finish);
        }
        if (pivotPos - start > 1) {
            push(stack, size, start);
            push(stack, size, pivotPos);
        }
    }

}

bool compareArrays(double* a1, int n1, double* a2, int n2){
    if (n1 != n2) return false;
    for (int i = 0; i < n1; i++) {
        if (a1[i] != a2[i]) return false;
    }
    return true;
}
