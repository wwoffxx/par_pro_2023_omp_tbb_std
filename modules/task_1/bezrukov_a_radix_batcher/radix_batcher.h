// Copyright 2023 Bezrukov Aleksandr
#ifndef MODULES_TASK_1_BEZRUKOV_A_RADIX_BATCHER_RADIX_BATCHER_H_
#define MODULES_TASK_1_BEZRUKOV_A_RADIX_BATCHER_RADIX_BATCHER_H_

#include <gtest/gtest.h>
#include <stdint.h>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

template <class T>
std::vector<int> createAndPrepareCounters(std::vector<T>* data, int offset, int count) {
    std::vector<int> counters(256 * sizeof(T));
    std::fill_n(counters.data(), counters.size(), 0);
    unsigned char* start = reinterpret_cast<unsigned char*>(
        data->data() + offset);
    unsigned char* stop = reinterpret_cast<unsigned char*>(
        data->data() + offset + count);

    while (start != stop) {
        for (int i = 0; i < static_cast<int>(sizeof(T)); i++) {
            counters[*start + 256 * i]++;
            start++;
        }
    }

    for (int i = 0; i < static_cast<int>(sizeof(T)); i++) {
        int sum = 0;
        if (counters[256 * i] == count)
            continue;
        for (int j = 0; j < 256; j++) {
            int tmp = counters[256 * i + j];
            counters[256 * i + j] = sum;
            sum += tmp;
        }
    }
    return counters;
}

template<class T>
void radixSort(std::vector<T>* data, int offset, int count) {
    std::vector<int> counters =
        createAndPrepareCounters(data, offset, count);

    std::vector<T> res(count);
    int j;
    for (j = 0; j < static_cast<int>(sizeof(T)); j++) {
        int* countersPtr = counters.data() + 256 * j;
        if (*countersPtr == count)
            break;

        T* dPtr, * rPtr;
        unsigned char* dataPtr;
        if (j % 2 == 0) {
            dPtr = data->data() + offset;
            dataPtr = reinterpret_cast<unsigned char*>(
                data->data() + offset);
            rPtr = res.data();
        } else {
            dPtr = res.data();
            dataPtr = reinterpret_cast<unsigned char*>(res.data());
            rPtr = data->data() + offset;
        }
        dataPtr += j;

        for (int i = 0; i < count; i++) {
            rPtr[*(countersPtr + *dataPtr)] = dPtr[i];
            *(countersPtr + *dataPtr) = *(countersPtr + *dataPtr) + 1;
            dataPtr += sizeof(T);
        }
    }

    if (j % 2 == 1) {
        for (int i = 0; i < count; i++)
            data->operator[](i + offset) = res[i];
    }
}

template<class T>
void mergeFragments(std::vector<T>* data, std::vector<T>* result,
    int offset1, int size1, int offset2, int size2, bool isLeft) {

    if (isLeft) {
        T* firstPtr = data->data() + offset1;
        int usedFirst = 0;

        T* secondPtr = data->data() + offset2;
        int usedSecond = 0;

        for (int i = 0; i < size1; i++) {
            if (usedFirst < size1 && usedSecond < size2) {
                if (*firstPtr < *secondPtr) {
                    result->operator[](i) = *firstPtr;
                    firstPtr++;
                    usedFirst++;
                } else {
                    result->operator[](i) = *secondPtr;
                    secondPtr++;
                    usedSecond++;
                }
            } else if (usedFirst < size1 && usedSecond >= size2) {
                result->operator[](i) = *firstPtr;
                firstPtr++;
                usedFirst++;
            } else if (usedFirst >= size1 && usedSecond < size2) {
                result->operator[](i) = *secondPtr;
                secondPtr++;
                usedSecond++;
            } else {
                throw "Impossible exception";
            }
        }
        return;
    }

    T* firstPtr = data->data() + offset1 + size1 - 1;
    int usedFirst = 0;

    T* secondPtr = data->data() + offset2 + size2 - 1;
    int usedSecond = 0;

    for (int i = size2 - 1; i >= 0; i--) {
        if (usedFirst < size1 && usedSecond < size2) {
            if (*firstPtr > *secondPtr) {
                result->operator[](i) = *firstPtr;
                firstPtr--;
                usedFirst++;
            } else {
                result->operator[](i) = *secondPtr;
                secondPtr--;
                usedSecond++;
            }
        } else if (usedFirst < size1 && usedSecond >= size2) {
            result->operator[](i) = *firstPtr;
            firstPtr--;
            usedFirst++;
        } else if (usedFirst >= size1 && usedSecond < size2) {
            result->operator[](i) = *secondPtr;
            secondPtr--;
            usedSecond++;
        } else {
            throw "Impossible exception";
        }
    }
}

int partner(int nodeIndex, int mergeStage, int mergeStageStep);

template<class T>
T getRandValue(T from, T to) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(from, to);
    return dist(gen);
}

template<class T>
void fillVecWithRandValues(T* data, int size, T from, T to) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(from, to);
    for (int i = 0; i < size; i++) {
        data[i] = dist(gen);
    }
}

template<class T>
bool isStrictAscending(T* data, int size, T startValue) {
    for (int i = 0; i < size; i++)
        if (data[i] != startValue++)
            return false;
    return true;
}

template<class T>
bool isStrictDescending(T* data, int size, T startValue) {
    for (int i = 0; i < size; i++)
        if (data[i] != startValue--)
            return false;
    return true;
}

template<class T>
void fillStrictAscending(T* data, int size, T startValue) {
    for (int i = 0; i < size; i++)
        data[i] = startValue++;
}

template<class T>
void fillStrictDescending(T* data, int size, T startValue) {
    for (int i = 0; i < size; i++)
        data[i] = startValue--;
}

template<class T>
void printVector(const std::vector<T>& vec) {
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

template<class T>
bool isAscending(T* data, int size) {
    for (int i = 1; i < size; i++) {
        if (data[i - 1] > data[i])
            return false;
    }
    return true;
}

template<class T>
bool isVecSame(const std::vector<T>& v1, const std::vector<T>& v2) {
    if (v1.size() != v2.size())
        return false;
    for (size_t i = 0; i < v1.size(); i++)
        if (v1[i] != v2[i])
            return false;
    return true;
}

#endif  // MODULES_TASK_1_BEZRUKOV_A_RADIX_BATCHER_RADIX_BATCHER_H_
