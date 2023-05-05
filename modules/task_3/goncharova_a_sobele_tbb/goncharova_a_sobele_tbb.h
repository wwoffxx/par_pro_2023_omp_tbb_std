// Copyright 2023 Goncharova Anna

#ifndef MODULES_TASK_3_GONCHAROVA_A_SOBELE_TBB_GONCHAROVA_A_SOBELE_TBB_H_
#define MODULES_TASK_3_GONCHAROVA_A_SOBELE_TBB_GONCHAROVA_A_SOBELE_TBB_H_

#include <vector>
#include <random>
#include <iostream>

template <class T>
struct image {
    std::vector<T> data;
    int rows{ 0 };
    int cols{ 0 };
    int size{ 0 };
    image() {}
    image(int r, int c);
    image(int r, int c, std::vector<T> d);
    image(const image<T>& img);
    void randImage(int r, int c);
    bool operator== (const image<T>& img) const;
    bool operator!= (const image<T>& img) const { return !(*this == img); }
};

/*----------------------------------------------------------------------*/
template<class T>
image<T>::image(int r, int c) {
    size = r * c;
    rows = r;
    cols = c;
    data.assign(size, 0);
}

template<class T>
image<T>::image(int r, int c, const std::vector<T>& d) {
    data = d;
    rows = r;
    cols = c;
    size = r * c;
}

template<class T>
image<T>::image(const image<T>& img) {
    data = img.data;
    rows = img.rows;
    cols = img.cols;
    size = img.size;
}

template<class T>
bool image<T>::operator==(const image<T>& img) const {
    if (rows == img.rows && cols == img.cols &&
        size == img.size && data == img.data)
        return true;

    else
        return false;
}

template<class T>
void image<T>::randImage(int r, int c) {
    size = r * c;
    rows = r;
    cols = c;
    data.resize(size);
    std::random_device rnd_device;
    std::mt19937 mersenne_engine{ rnd_device() };
    std::uniform_int_distribution<int> uint_dist{ 0, 256 };
    auto gen = [&uint_dist, &mersenne_engine]() {
        return uint_dist(mersenne_engine);
    };
    generate(begin(data), end(data), gen);
}


using imageU = image<uint8_t>;
using imageS = image<char>;

imageU  sobel_par(const imageU& img);
imageU  sobel_seq(const imageU& img);

#endif  // MODULES_TASK_3_GONCHAROVA_A_SOBELE_TBB_GONCHAROVA_A_SOBELE_TBB_H_
