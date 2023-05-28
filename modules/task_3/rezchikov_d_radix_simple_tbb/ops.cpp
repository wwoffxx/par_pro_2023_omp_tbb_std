// Copyright 2023 Rezchikov Dmitrii

#include <omp.h>
#include <tbb/tbb.h>
#include "../../../modules/task_3/rezchikov_d_radix_simple_tbb/ops.h"


class tbb_functor{
 public:
    std::vector<int> res;

    tbb_functor() = default;
    tbb_functor(const tbb_functor& src, tbb::split) {}

    void operator()(const tbb::blocked_range<std::vector<int>::iterator>& range) {
        std::copy(range.begin(), range.end(), res.begin());
        radSortSeq(&res);
    }

    void join(const tbb_functor& rhs) {
        res = merge(&res, &rhs.res);
    }
};

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
    tbb_functor func;
    std::vector<int> result;

    tbb::parallel_reduce(
        tbb::blocked_range<std::vector<int>::iterator>(
            vec->begin(), vec->end())
        , func);
    return func.res;
}


std::vector<int> merge(const std::vector<int> * v1,
                        const std::vector<int> * v2) {
    std::vector<int> res(v1->size() + v2->size());
    std::merge(v1->begin(), v1->end(), v2->begin(), v2->end(), res.begin());
    return res;
}
