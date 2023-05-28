// Copyright 2023 Terina Alina
#include <tbb/tbb.h>
#include <random>
#include <climits>
#include <functional>
#include <algorithm>
#include <stdexcept>

#include "../../../modules/task_3/terina_a_quicksort_smpl_merg/quicksort.h"

std::vector<int> getRandomVector(int size) {
    std::random_device dev;
    std::mt19937 randomGenerator(dev());
    std::uniform_int_distribution<int> randomValue(1, 100);
    std::vector<int> our_vector(size);
    for (int& item : our_vector) {
        item = randomValue(randomGenerator);
    }
    return our_vector;
}

void quickSort(int l, int r, std::vector <double>* list) {
    while (r > l) {
        int lo = l;
        int hi = r;
        int p = list->at((l + r) / 2);
        while (lo <= hi) {
            while (list->at(lo) < p) {
                lo++;
            }
            while (list->at(hi) > p) {
                hi--;
            }
            if (lo <= hi) {
                std::swap(list->at(lo), list->at(hi));
                lo++;
                hi--;
            }
        }
        if (2 * lo > l + r) {
            quickSort(lo, r, list);
            r = lo - 1;
        } else {
            quickSort(l, lo - 1, list);
            l = lo;
        }
    }
    return;
}
std::vector<int> merge(const std::vector<int>& vec1,
    const std::vector<int>& vec2) {
    std::vector<int> merged(vec1.size() + vec2.size());
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < static_cast<int>(vec1.size())
        && j < static_cast<int>(vec2.size())) {
        if (vec1[i] < vec2[j]) {
            merged[k] = vec1[i];
            i++;
        } else {
            merged[k] = vec2[j];
            j++;
        }
        k++;
    }
    while (i < static_cast<int>(vec1.size())) {
        merged[k] = vec1[i];
        k++;
        i++;
    }
    while (j < static_cast<int>(vec2.size())) {
        merged[k] = vec2[j];
        k++;
        j++;
    }

    return merged;
}
void quicksort(std::vector<int>* our_vector, int left, int right) {
    if (left < right) {
        int sep_ind = separation(our_vector, left, right);
        quicksort(our_vector, left, sep_ind - 1);
        quicksort(our_vector, sep_ind + 1, right);
    }
}

void _quickSort(std::vector<int>* our_vector) {
    int number = 4;
    if (static_cast<int>(our_vector->size()) < number) {
        quicksort(our_vector, 0, our_vector->size() - 1);
        return;
    }
    if (our_vector->size() == 1) {
        return;
    }
    tbb::task_group g;

    int numbersinsgmt = our_vector->size() / number;

    std::vector<std::vector<int>> sgmnts;
    std::vector<int> sgmnt;

    for (int i = 0; i < number; i++) {
        if (i == number - 1) {
            sgmnt.insert(sgmnt.end(),
                our_vector->begin() + i * numbersinsgmt,
                our_vector->end());
        } else {
            sgmnt.insert(sgmnt.end(), our_vector->begin() + i * numbersinsgmt,
                our_vector->begin() + (i + 1) * numbersinsgmt);}
        sgmnts.push_back(sgmnt);
        sgmnt.clear();
    }

    tbb::parallel_for(
        tbb::blocked_range<size_t>(0, sgmnts.size(), 1),
        [&sgmnts](const tbb::blocked_range<size_t>& range) {
            for (size_t i = range.begin(); i != range.end(); ++i) {
                quicksort(&sgmnts[i], 0, sgmnts[i].size() - 1);
            }
        },
        tbb::simple_partitioner());

    *our_vector = sgmnts[0];
    for (size_t i = 1; i < sgmnts.size(); i++) {
        *our_vector = merge(*our_vector, sgmnts[i]);
    }
}
int separation(std::vector<int>* our_vector, int left, int right) {
    int pivot = our_vector->at(right);
    int smallerElementIndex = left - 1;

    for (int i = left; i < right; i++) {
        if (our_vector->at(i) < pivot) {
            std::swap(our_vector->at(++smallerElementIndex), our_vector->at(i));
        }
    }

    std::swap(our_vector->at(smallerElementIndex + 1), our_vector->at(right));

    return smallerElementIndex + 1;
}

void genrndArr(double* arr, int n) {
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<> uid(0, n);
    for (int i = 0; i < n; i++) {
        arr[i] = uid(gen);
    }
}
