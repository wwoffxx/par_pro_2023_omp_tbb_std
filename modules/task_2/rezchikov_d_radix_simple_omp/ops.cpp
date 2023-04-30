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

void mergeRadixSort(std::vector<int> * vec) {
    if (vec->size() < 2) {
        return;
    }
    int pvt = vec->size() / 2;

    std::vector<int> v1(vec->begin(), vec->begin() + pvt);
    std::vector<int> v2(vec->begin() + pvt, vec->end() );

    radSortSeq(&v1);
    radSortSeq(&v2);

    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vec->begin());
}

std::vector<int> getRndVector(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());

    std::vector<int> res(size);

    for (int i = 0; i < size; ++i) {
        res[i] = gen() % 1000;
    }
    return res;
}

void radSortPar( std::vector<int> & vec ){
    if ( vec.size() < 2 ){
        return;
    }
    std::string result = "";
    std::string myArr[4] = {"","","",""};
    std::string myArr2[4] = {"","","",""};
    int diff;
    #pragma omp parallel shared(diff)
    {
        
        #pragma omp single
            {
                diff = vec.size() - ( vec.size() / omp_get_num_threads() ) * omp_get_num_threads();
                // std::cout << diff << std::endl;
            }        
        #pragma omp for
        for ( int i = 0; i < omp_get_num_threads(); ++i){
            // std::cout << diff << std::endl;
            int thread_num = omp_get_thread_num();
            int threads_num = omp_get_num_threads();
            int l, r;
            l = thread_num == 0
                            ? 0
                            : thread_num * (vec.size() / threads_num);
            if ( thread_num != 0){
                l += (thread_num + 1) <= diff
                                        ? thread_num
                                        : diff;
            }
            r = thread_num == threads_num - 1
                            ? vec.size()
                            : (thread_num + 1 ) * (vec.size() / threads_num );
            if ( thread_num != (threads_num - 1) ){
                r += (thread_num + 1) <= diff
                                        ? thread_num + 1
                                        : diff;
            }
            // myArr[omp_get_thread_num()] = "thread #" + std::to_string(omp_get_thread_num()) + ": l = " + std::to_string(l) + ", r = " + std::to_string(r) + "\n";
            

        
        }
        #pragma omp for
            for (int i = 0; i < vec.size(); ++i){
                myArr2[omp_get_thread_num()] += std::to_string(i) + " ";
            }
    }

    for(auto & s : myArr ){
        std::cout << s;
    }
    for(auto & s : myArr2 ){
        std::cout << s << "\n";
    }

}

int main(){

    auto arr = getRndVector(24);

    radSortPar(arr);

    return 0;
}
