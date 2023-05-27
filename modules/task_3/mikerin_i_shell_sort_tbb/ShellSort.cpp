// Copyright 2023 Mikerin Ilya

#include "ShellSort.h"

int D[] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};

std::vector<double> getRandomVector(int  sz) {
    std::vector<double> vec(sz);
    srand(time(nullptr));
    for (int  i = 0; i < sz; i++) { vec[i] = static_cast<double>(rand()) * 100 / RAND_MAX - 50; } //NOLINT
    return vec;
}

void MergeSort(std::vector<double> &vec, std::size_t first, std::size_t second ) { //NOLINT
    if ( second-first > 0 ) {
        int center = static_cast<int>((first + second) / 2);

        MergeSort(vec, first, center);
        MergeSort(vec, center + 1, second);

        int i = first, j = center + 1, k = 0;
        std::vector<double> newVec = std::vector<double>(second-first + 1);

        for ( k = 0; k < second - first + 1; k++ ) {
            if (vec[i] <= vec[j]) {
                newVec[k] = vec[i];
                i++;
            } else {
                newVec[k] = vec[j];
                j++;
            }

            if (i > center || j > second) break;
        }
        k++;

        if (i > center) {
            for (; k< second - first + 1; k++) {
                newVec[k] = vec[j];
                j++;
            }
        } else {
            for (; k< second - first + 1; k++) {
                newVec[k] = vec[i];
                i++;
            }
        }

        for (int k = 0; k< second - first + 1; k++) {
            vec[first + k] = newVec[k];
        }
    }
}

void ShellSort(std::vector<double> &vec) { //NOLINT
    int  i = 0;

    if (vec.size() > D[8]) {
        i = 8;
    } else {
        while (D[i] < vec.size()) i++;
        i--;
    }

    while (i >= 0) {
        std::vector<std::vector<double>> vecArray =
                std::vector<std::vector<double>>(D[i]);

        for (int j =0; j< vecArray.size(); j++) {
            int l = 0;

            do {
                vecArray[j].push_back(vec.at(j + D[i] * l));
                l++;
            } while (j + D[i] * l < vec.size() );
        }

        for (int j =0; j< vecArray.size(); j++) {
            MergeSort(vecArray[j], 0, vecArray[j].size()-1);
        }

        for (int j = 0; j< vecArray.size(); j++) {
            for (int k = 0; k< vecArray[j].size(); k++) {
                vec[j + k * D[i]] = vecArray[j][k];
            }
        }
        i--;
    }
}



int MinCountForRecursion = 50;
int MinCountForParallel = 100;

void MergeSortTBB(std::vector<double> &vec, std::size_t first, std::size_t second) { //NOLINT
    if ( second-first > 0 ) {
        int center = static_cast<int>((first + second) / 2);

        if (second-first > MinCountForParallel) {
            tbb::parallel_invoke(
                    [&] { MergeSortTBB(vec, first, center);},
                    [&] {MergeSortTBB(vec, center + 1, second);});
        } else {
            MergeSortTBB(vec, first, center);
            MergeSortTBB(vec, center + 1, second);
        }

        int i = first, j = center + 1, k = 0;
        std::vector<double> newVec = std::vector<double>(second-first + 1);

        for ( k = 0; k < second - first + 1; k++ ) {
            if (vec[i] <= vec[j]) {
                newVec[k] = vec[i];
                i++;
            } else {
                newVec[k] = vec[j];
                j++;
            }

            if (i > center || j > second) break;
        }
        k++;

        if (i > center) {
            for (; k< second - first + 1; k++) {
                newVec[k] = vec[j];
                j++;
            }
        } else {
            for (; k< second - first + 1; k++) {
                newVec[k] = vec[i];
                i++;
            }
        }

        for (int k = 0; k< second - first + 1; k++) {
            vec[first + k] = newVec[k];
        }
    }
}

//  class MergeCall {
//
//    std::vector<std::vector<double >> Vec;
//
//  public:
//    MergeCall(std::vector<std::vector<double >> &vec){
//        Vec = std::vector< std::vector<double>>();
//        for(std::vector<double> i : vec){
//            Vec.push_back(i);
//        }
//    }
//
//    void operator()(const tbb::blocked_range<int>& range) const
//    {
//        int begin = range.begin();
//        int end = range.end();
//        for(int i = begin; i != end;i++){
//            MergeSortTBB(const_cast<std::vector<double>&> (Vec[i]),
//                          0, (Vec[i]).size()-1);
//        }
//    }
//};

void ShellSortTBB(std::vector<double> &vec) { //NOLINT
    int  i = 0;

    if (vec.size() > D[8]) {
        i = 8;
    } else {
        while (D[i] < vec.size()) i++;
        i--;
    }

    while (i >= 0) {
        std::vector<std::vector<double>> vecArray =
                std::vector<std::vector<double>>(D[i]);

        for (int j =0; j< vecArray.size(); j++) {
            int l = 0;

            do {
                vecArray[j].push_back(vec.at(j + D[i] * l));
                l++;
            } while (j + D[i] * l < vec.size() );
        }

       // tbb::parallel_for(tbb::blocked_range<int>(0,vecArray.size()),
       // MergeCall(vecArray));
        for (int j =0; j< vecArray.size(); j++) {
            MergeSortTBB(vecArray[j], 0, vecArray[j].size()-1);
        }

        for (int j = 0; j< vecArray.size(); j++) {
            for (int k = 0; k< vecArray[j].size(); k++) {
                vec[j + k * D[i]] = vecArray[j][k];
            }
        }
        i--;
    }
}

