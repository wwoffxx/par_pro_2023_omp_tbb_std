// Copyright 2023 Nosonova Darina

#include <gtest/gtest.h>
#include <bitset>
#include <list>
#include <random>
#include <vector>

union convDouble {
    double d;
    unsigned char ch[8];
};

struct Arr {
    int size;
    double *arr;
};

convDouble *SeqRadixSort(convDouble *arr, int size) {
    std::vector<std::vector<convDouble>> cArr(256);
    int digit = 0;
    // first bait initialization
    for (int i = 0; i < size; i++) {
        int zn{static_cast<int>(arr[i].ch[digit])};
        cArr.at(zn).push_back(arr[i]);
    }
    digit++;

    // 1-7 bait
    for (; digit <= 7; digit++) {
        std::vector<std::vector<convDouble>> reachVector(256);
        for (int i = 0; i < 256; i++) {
            for (auto j : cArr.at(i)) {
                int zn{static_cast<int>(j.ch[digit])};
                reachVector.at(zn).push_back(j);
            }
        }
        cArr = reachVector;
    }
    std::list<convDouble> resVec;
    for (int i = 0; i < 256; i++) {
        for (auto j : cArr.at(i)) {
            int zn = static_cast<int>(j.ch[7]);
            if (zn & 128)
                resVec.push_front(j);
            else
                resVec.push_back(j);
        }
    }
    // convertation
    convDouble *res = new convDouble[size];
    int i = 0;
    for (auto it : resVec) {
        res[i] = it;
        i++;
    }
    return res;
}

std::list<double> RadixSort(std::list<double> arr) {
    convDouble *sortArr = new convDouble[arr.size()];
    std::list<double> res;
    int iter = 0;
    for (auto i : arr) {
        sortArr[iter].d = i;
        iter++;
    }
    convDouble *resArr = SeqRadixSort(sortArr, arr.size());
    for (int i = 0; i < arr.size(); i++) {
        res.push_back(resArr[i].d);
    }
    delete[] sortArr;
    delete[] resArr;
    return res;
}

std::list<double> Merge(std::list<double> A, std::list<double> B) {
    std::list<double> res;
    auto i = A.begin();
    auto j = B.begin();
    while (i != A.end() && j != B.end()) {
        if (*i < *j) {
            res.push_back(*i);
            ++i;
        } else {
            res.push_back(*j);
            ++j;
        }
    }
    while (i != A.end()) {
        res.push_back(*i);
        ++i;
    }
    while (j != B.end()) {
        res.push_back(*j);
        ++j;
    }
    return res;
}

std::list<double> MergeRadixSort(std::list<double> arr, int k) {
    int halfSize = arr.size() / k;
    int ost = arr.size() % halfSize;
    std::vector<std::list<double>> arrays(k);
    int iterSize = halfSize + ost;
    int i = 0;
    int iteration = 0;
    for (auto iter : arr) {
        arrays.at(iteration).push_back(iter);
        if (i == iterSize) {
            iteration++;
            i = 0;
            iterSize = halfSize;
        }
    }
    for (auto iter = arrays.begin(); iter != arrays.end(); ++iter) {
        *iter = RadixSort(*iter);
    }
    std::list<double> res;
    for (auto iter = arrays.begin(); iter != arrays.end(); ++iter) {
        res = Merge(res, *iter);
    }
    return res;
}

std::list<double> getRandList(int size, double lower_bound,
                              double upper_bound) {
    std::list<double> res;
    for (int i = 0; i < size; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        int r = static_cast<int>(gen());
        res.push_back(lower_bound +
                      (upper_bound - lower_bound) * (r % RAND_MAX) / RAND_MAX);
    }
    return res;
}

void outList(std::list<double> list) {
    for (auto i : list) {
    }
}

bool isSorted(std::list<double> arr) {
    for (auto i = arr.begin(); i != arr.end(); ++i) {
        if (i == arr.begin()) ++i;
        auto j = i;
        --j;
        if (*i < *j) return false;
    }
    return true;
}



TEST(Sequential, Test_MergeRadixSort_1) {
    int size = 20;
    int lower_bound = -100;
    int upper_bound = 100;
    std::list<double> list = getRandList(size, lower_bound, upper_bound);
    list = MergeRadixSort(list, 4);
    EXPECT_TRUE(isSorted(list));
}

TEST(Sequential, Test_MergeRadixSort_2) {
    int size = 30;
    int lower_bound = -1000;
    int upper_bound = 1000;
    std::list<double> list = getRandList(size, lower_bound, upper_bound);
    list = MergeRadixSort(list, 15);
    EXPECT_TRUE(isSorted(list));
}

TEST(Sequential, Test_MergeRadixSort_3) {
    int size = 100;
    int lower_bound = -100;
    int upper_bound = 100;
    std::list<double> list = getRandList(size, lower_bound, upper_bound);
    list = MergeRadixSort(list, 50);
    EXPECT_TRUE(isSorted(list));
}

TEST(Sequential, Test_MergeRadixSort_4) {
    int size = 1000;
    int lower_bound = -1000;
    int upper_bound = 1000;
    std::list<double> list = getRandList(size, lower_bound, upper_bound);
    list = MergeRadixSort(list, 100);
    EXPECT_TRUE(isSorted(list));
}

TEST(Sequential, Test_MergeRadixSort_5) {
    int size = 1500;
    int lower_bound = -500;
    int upper_bound = 500;
    std::list<double> list = getRandList(size, lower_bound, upper_bound);
    list = MergeRadixSort(list, 4);
    EXPECT_TRUE(isSorted(list));
}
