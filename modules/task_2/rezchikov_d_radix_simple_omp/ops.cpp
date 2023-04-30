// Copyright 2023 Rezchikov Dmitrii

#include <omp.h>
#include "../../../modules/task_2/rezchikov_d_radix_simple_omp/ops.h"


void countingSortSeq(std::vector<int> * array, int l, int r, int place) {
    const int max = 10;
    int size = r - l;
    std::vector<int> output(size);
    std::vector<int> count(max);

    for (int i = 0; i < max; ++i)
        count[i] = 0;

    // Calculate count of elements
    for (int i = l; i < r; ++i)
        count[((*array)[i] / place) % 10]++;

    // Calculate cumulative count
    for (int i = 1; i < max; ++i)
        count[i] += count[i - 1];

    // Place the elements in sorted order
    for (int i = r - 1; i >= l; --i) {
        count[((*array)[i] / place) % 10]--;
        output[count[((*array)[i] / place) % 10]] = (*array)[i];
    }
    for (int i = l; i < r; i++)
        (*array)[i] = output[i];
}

void countingSortPar(std::vector<int> * array, int l, int r, int place) {
    const int max = 10;
    int size = r - l;
    std::vector<int> output(size);
    std::vector<int> count(max);

    #pragma parallel shared(output, count)
    {
        #pragma for
        for (int i = 0; i < max; ++i)
            count[i] = 0;

        // Calculate count of elements
        #pragma for
        for (int i = l; i < r; ++i)
            #pragma atomic
                count[((*array)[i] / place) % 10]++;

        // Calculate cumulative count
        #pragma single
        for (int i = 1; i < max; ++i)
            count[i] += count[i - 1];

        // Place the elements in sorted order
        #pragma for
        for (int i = r - 1; i >= l; --i) {
            #pragma atomic
                count[((*array)[i] / place) % 10]--;
            output[count[((*array)[i] / place) % 10]] = (*array)[i];
        }
        #pragma for
        for (int i = l; i < r; i++)
            (*array)[i] = output[i];
    }
}

void radSortSeq(std::vector<int> * vec) {
    if ( vec->size() < 2 ) {
        return;
    }
    int len = std::floor(
                        std::log10(
                            *std::max_element(vec->begin(), vec->end()))) + 1;
    int pow = 1;

    for (int i = 0; i < len; ++i) {
        countingSortSeq(vec, 0, vec->size(), pow);
        pow *= 10;
    }
}

void radSortPar(std::vector<int> * vec) {
    if ( vec->size() < 2 ) {
        return;
    }
    int len = std::floor(
                        std::log10(
                            *std::max_element(vec->begin(), vec->end()))) + 1;
    #pragma parallel shared(vec)
    {
        int pow = 1;
        #pragma for
        for (int i = 0; i < len; ++i) {
            countingSortPar(vec, 0, vec->size(), pow);
            pow *= 10;
        }
    }
        // for (int i = 0; i < len; ++i) {
        //     countingSortPar(vec, 0, vec->size(), pow);
        //     pow *= 10;
        // }
}

std::vector<int> getRndVector(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());

    std::vector<int> res(size);

    for (int i = 0; i < size; ++i) {
        res[i] = gen() % 10;
    }
    return res;
}

std::vector<int> radSortParMerge(std::vector<int> * vec) {
    if ( vec->size() < 2 ) {
        return *vec;
    }
    int size = vec->size();
    std::vector<int> result;
    #pragma omp parallel shared(vec, result)
    {
        int diff;
        #pragma omp single
        {
            diff = size - (size/omp_get_num_threads())*omp_get_num_threads();
        }
        int thread_num = omp_get_thread_num();
        int threads_num = omp_get_num_threads();
        int l, r;
        l = thread_num == 0
                        ? 0
                        : thread_num * (size / threads_num);
        if ( thread_num != 0 ) {
            l += (thread_num + 1) <= diff
                                    ? thread_num
                                    : diff;
        }
        auto lPtr = vec->begin() + l;
        r = thread_num == threads_num - 1
                        ? size
                        : (thread_num + 1) * (size / threads_num);
        if ( thread_num != (threads_num - 1) ) {
            r += (thread_num + 1) <= diff
                                    ? thread_num + 1
                                    : diff;
        }
        auto rPtr = vec->begin() + r;
        std::vector<int> tmpVec;
        tmpVec = std::vector<int>(lPtr, rPtr);
        radSortSeq(&tmpVec);
        #pragma omp critical
            result = merge(&result, &tmpVec);
    }
    return result;
    // *vec = result;
}

std::vector<int> merge(std::vector<int> * v1, std::vector<int> * v2) {
    std::vector<int> res(v1->size() + v2->size());
    std::merge(v1->begin(), v1->end(), v2->begin(), v2->end(), res.begin());
    return res;
}
