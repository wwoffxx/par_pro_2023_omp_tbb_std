// Copyright 2023 Bezrukov Aleksandr
#ifndef MODULES_TASK_2_BEZRUKOV_A_RADIX_BATCHER_RADIX_BATCHER_H_
#define MODULES_TASK_2_BEZRUKOV_A_RADIX_BATCHER_RADIX_BATCHER_H_

#include <gtest/gtest.h>
#include <omp.h>
#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <exception>

int companion(int mStage, int mStageStep, int ndeIndex);

template <class T>
void printVector(const std::vector<T>& vec) {
    for (int i = 0; i < vec.size(); ++i) std::cout << vec[i] << " ";
    std::cout << "\n";
}

template <class T>
T getRandValue(const T& min, const T& max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(min, max);
    return dist(gen);
}

template <class T>
void fillArrRandomly(T* arr, int size, const T& min, const T& max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(min, max);
    for (int i = 0; i < size; ++i) arr[i] = dist(gen);
}

template <class T>
void fillArrStrictDescending(T* arr, int size, T startValue) {
    for (int i = 0; i < size; ++i) {
        arr[i] = startValue;
        startValue -= 1;
    }
}

template <class T>
bool areVecsEqual(const std::vector<T>& vec1, const std::vector<T>& vec2) {
    if (vec1.size() != vec2.size()) return false;

    for (int i = 0; i < static_cast<int>(vec1.size()); ++i)
        if (vec2[i] != vec1[i]) return false;
    return true;
}

template <class T>
std::vector<int> prepareCounters(std::vector<T>* vec, int offset, int count) {
    std::vector<int> counters(sizeof(T) * 256);
    std::fill_n(counters.data(), counters.size(), 0);

    unsigned char* start =
        reinterpret_cast<unsigned char*>(vec->data() + offset);
    unsigned char* stop =
        reinterpret_cast<unsigned char*>(vec->data() + offset + count);

    while (start != stop) {
        for (int i = 0; i < static_cast<int>(sizeof(T)); ++i)
            ++counters[*start + i * 256], ++start;
    }

    for (int i = 0; i < static_cast<int>(sizeof(T)); ++i) {
        int sum = 0;
        if (counters[i * 256] == count) continue;
        for (int j = 0; j < 256; ++j) {
            int tmp = counters[j + i * 256];
            counters[j + i * 256] = sum;
            sum = tmp + sum;
        }
    }

    return counters;
}

template <class T>
void RadixSortSeq(std::vector<T>* vec, int offset, int count) {
    std::vector<int> counters = prepareCounters(vec, offset, count);

    std::vector<T> res(count);
    int j;
    for (j = 0; j < static_cast<int>(sizeof(T)); ++j) {
        int* countersPtr = 256 * j + counters.data();
        if (count == (*countersPtr)) break;

        T *dPtr, *rPtr;
        unsigned char* dataPtr;
        if (j % 2 == 0) {
            dPtr = offset + vec->data();
            dataPtr = reinterpret_cast<unsigned char*>(offset + vec->data());
            rPtr = res.data();
        } else {
            dPtr = res.data();
            dataPtr = reinterpret_cast<unsigned char*>(res.data());
            rPtr = offset + vec->data();
        }
        dataPtr = dataPtr + j;

        for (int i = 0; i < count; ++i) {
            rPtr[*(*dataPtr + countersPtr)] = dPtr[i];
            *(*dataPtr + countersPtr) = *(*dataPtr + countersPtr) + 1;
            dataPtr = dataPtr + sizeof(T);
        }
    }

    if (j % 2 == 1) {
        for (int i = 0; i < count; ++i) vec->operator[](offset + i) = res[i];
    }
}

template <class T>
void BatcherParrallelMerge(T* vec, T* res, T* companionData, int blkSize,
                           int ownID, int companionID) {
    if (ownID == companionID) return;

    bool isLeft = ownID < companionID;

    if (isLeft) {
        T* firstPtr = vec;
        T* secondPtr = companionData;

        int usedFirst = 0;
        int usedSecond = 0;

        for (int i = 0; i < blkSize; ++i) {
            if (usedFirst < blkSize && usedSecond < blkSize) {
                if (*firstPtr < *secondPtr) {
                    res[i] = *firstPtr;
                    ++usedFirst;
                    ++firstPtr;
                } else {
                    res[i] = *secondPtr;
                    ++usedSecond;
                    ++secondPtr;
                }
            } else if (usedFirst < blkSize && usedSecond >= blkSize) {
                res[i] = *firstPtr;
                ++usedFirst;
                ++firstPtr;
            } else if (usedFirst >= blkSize && usedSecond < blkSize) {
                res[i] = *secondPtr;
                ++usedSecond;
                ++secondPtr;
            } else {
                throw std::runtime_error("Ex");
            }
        }
        return;
    }

    T* firstPtr = blkSize - 1 + vec;
    T* secondPtr = blkSize - 1 + companionData;

    int usedFirst = 0;
    int usedSecond = 0;

    for (int i = blkSize - 1; i > -1; --i) {
        if (usedFirst < blkSize && usedSecond < blkSize) {
            if (*firstPtr > *secondPtr) {
                res[i] = *firstPtr;
                ++usedFirst;
                --firstPtr;
            } else {
                res[i] = *secondPtr;
                ++usedSecond;
                --secondPtr;
            }
        } else if (usedFirst < blkSize && usedSecond >= blkSize) {
            res[i] = *firstPtr;
            ++usedFirst;
            --firstPtr;
        } else if (usedFirst >= blkSize && usedSecond < blkSize) {
            res[i] = *secondPtr;
            ++usedSecond;
            --secondPtr;
        } else {
            throw std::runtime_error("Ex2");
        }
    }
}

template <class T>
void RadixBatcherSort(std::vector<T>* vec, int deg) {
    if (deg == 0) {
        RadixSortSeq<T>(vec, 0, vec->size());
        return;
    }

    int threadsCount = (1 << deg);
    if (threadsCount > static_cast<int>(vec->size())) {
        RadixSortSeq<T>(vec, 0, vec->size());
        return;
    }

    int oldSize = static_cast<int>(vec->size());
    bool isResized = false;
    if (oldSize % threadsCount != 0) {
        vec->resize(oldSize + (threadsCount - oldSize % threadsCount), ~0);
        isResized = true;
    }

    int size = vec->size();
    int blkSize = size / threadsCount;

    std::vector<T> res(size);

    T** min = new T*[threadsCount];
    T** max = new T*[threadsCount];

    for (int i = 0; i < threadsCount; ++i) {
        min[i] = vec->data() + blkSize * i;
        max[i] = res.data() + blkSize * i;
    }

    T* mainData = vec->data();

    #pragma omp parallel num_threads(threadsCount)
    {
        int ownID = omp_get_thread_num();
        RadixSortSeq<T>(vec, ownID * blkSize, blkSize);

        #pragma omp barrier

        int companionID;

        for (int stage = 1; stage < deg + 1; ++stage) {
            for (int step = 1; step < stage + 1; ++step) {
                companionID = companion(stage, step, ownID);

                BatcherParrallelMerge(min[ownID], max[ownID], min[companionID],
                                      blkSize, ownID, companionID);
                #pragma omp barrier
                if (companionID != ownID) std::swap(min[ownID], max[ownID]);
                #pragma omp barrier

                if (stage == deg && step == deg) {
                    for (int i = 0; i < blkSize; ++i)
                        mainData[i + ownID * blkSize] = min[ownID][i];
                }
            }
        }
        #pragma omp barrier
    }
    if (isResized) vec->resize(oldSize);
    delete[] max;
    delete[] min;
}

#endif  // MODULES_TASK_2_BEZRUKOV_A_RADIX_BATCHER_RADIX_BATCHER_H_
