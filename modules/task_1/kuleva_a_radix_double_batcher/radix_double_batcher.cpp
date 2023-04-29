// Copyright 2023 Kuleva Anna
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>
#include "../../../modules/task_1/kuleva_a_radix_double_batcher/radix_double_batcher.h"


using ull = uint64_t;

const int preMask = (1 << 8);

union {
    ull asLong;
    double asDouble;
} value;

ull getOffset(ull value, int exp) {
    return (value >> (8 * exp));
}

void radixSortForExp(std::vector<double>* _base, int exp) {
    auto& base = *_base;
    std::vector<double> result(base.size());
    std::vector<int> sorterArray((1 << 8), 0);
    int mask = preMask - 1;

    for (double element : base) {
        value.asDouble = element;
        const int expValue = mask & getOffset(value.asLong, exp);
        sorterArray[expValue]++;
    }

    for (int i = 1; i < sorterArray.size(); i++) {
        sorterArray[i] += sorterArray[i - 1];
    }

    for (int i = base.size() - 1; i >= 0; i--) {
        value.asDouble = base[i];
        const int expValue = mask & getOffset(value.asLong, exp);
        result[sorterArray[expValue] - 1] = base[i];
        sorterArray[expValue]--;
    }

    for (int i = 0; i < base.size(); i++)
        base[i] = result[i];
}

void radixSort(std::vector<double>* _base) {
    auto& base = *_base;
    int maxExp = sizeof(double);

    std::vector<double> negative, positive;

    std::copy_if(base.begin(), base.end(), std::back_inserter(negative), [](double x) { return x < 0; });
    std::copy_if(base.begin(), base.end(), std::back_inserter(positive), [](double x) { return x >= 0; });

    for (int exp = 0; exp < maxExp; exp++) {
        radixSortForExp(&negative, exp);
        radixSortForExp(&positive, exp);
    }

    auto last = std::copy(negative.rbegin(), negative.rend(), base.begin());
    std::copy(positive.begin(), positive.end(), last);
}

void compareAndExchange(double* a, double* b) {
    if (*b < *a) std::swap(*a, *b);
}

std::vector<double> shuffle(const std::vector<double>& left, const std::vector<double>& right) {
    std::vector<double> result(left.size() + right.size());
    for (int i = 0, j = 0; i < result.size(); i += 2, j++) {
        result[i] = left[j];
        result[i + 1] = right[j];
    }
    return result;
}

std::vector<double> batcherMerge(const std::vector<double>& left, const std::vector<double>& right) {
    auto result = shuffle(left, right);
    std::merge(left.begin(), left.end(), right.begin(), right.end(), result.begin());
    for (int i = 0; i < result.size(); i += 2)
        compareAndExchange(&result[i], &result[i + 1]);
    int halfSize = result.size() / 2;
    for (int i = 0; i + halfSize < result.size(); i++)
        compareAndExchange(&result[i], &result[i + halfSize]);
    return result;
}

std::vector<double> radixBatcherSort(const std::vector<double>& base) {
    int size = (base.size() % 2 != 0) ? base.size() + 1 : base.size();

    const int half = size / 2;
    std::vector<double> left(base.begin(), base.begin() + half);
    std::vector<double> right(base.begin() + half, base.end());

    if (base.size() % 2 != 0)
        right.push_back(std::numeric_limits<double>::max());

    radixSort(&left);
    radixSort(&right);

    auto result = batcherMerge(left, right);

    if (base.size() % 2 != 0)
        result.pop_back();

    return result;
}
