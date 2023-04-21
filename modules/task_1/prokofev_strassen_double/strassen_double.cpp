  // Copyright 2022 Prokofev Denis

#include <../../../modules/task_1/prokofev_strassen_double/strassen_double.h>
#include <random>
#include <ctime>
#include <vector>

std::vector<double> rndMat(int msize) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<double> vec(msize * msize);
    for (int i = 0; i < msize * msize; i++) {
        vec[i] = gen() % 9 + 1;
    }
    return vec;
}

std::vector<double> mMult(const std::vector<double>& a,
    const std::vector<double>& b, unsigned int msize) {
    std::vector<double> res(msize * msize);
    for (unsigned int i = 0; i < msize; i++)
        for (unsigned int j = 0; j < msize; j++) {
            for (unsigned int k = 0; k < msize; k++)
                res[j + i * msize] += a[i * msize + k] * b[j + k * msize];
        }
    return res;
}

std::vector<double> sum(const std::vector<double>& a,
    const std::vector<double>& b, unsigned int msize) {
    unsigned int size = msize * msize;
    std::vector<double> res(size);
    for (unsigned int i = 0; i < size; i++) {
        res[i] = round((a[i] + b[i])*100)/100;
    }
    return res;
}

std::vector<double> diff(const std::vector<double>& a,
    const std::vector<double>& b, unsigned int msize) {
    unsigned int size = msize * msize;
    std::vector<double> res(size);
    for (unsigned int i = 0; i < size; i++) {
        res[i] = a[i] - b[i];
    }
    return res;
}

void splitMatrix(const std::vector<double>& matr, std::vector<double>* a,
    std::vector<double>* b, std::vector<double>* c, std::vector<double>* d,
    unsigned int size) {
    unsigned int msize = size / 2;
    for (unsigned int i = 0; i < msize; i++) {
        for (unsigned int j = i * 2 * msize; j < i * 2 * msize + msize; j++)
            a->push_back(matr[j]);
        for (unsigned int j = i * 2 * msize + msize; j < i * 2 * msize +
        2 * msize; j++)
            b->push_back(matr[j]);
    }
    for (unsigned int i = msize; i < 2 * msize; i++) {
        for (unsigned int j = i * 2 * msize; j < i * 2 * msize + msize; j++)
            c->push_back(matr[j]);
        for (unsigned int j = i * 2 * msize + msize; j < i * 2 *
            msize + 2 * msize; j++)
            d->push_back(matr[j]);
    }
}

void mergeMatrix(std::vector<double>* matr, const std::vector<double>& a,
    const std::vector<double>& b,
    const std::vector<double>& c, const std::vector<double>& d,
    unsigned int size) {
    unsigned int msize = size / 2;
    for (unsigned int i = 0; i < msize; i++) {
        for (unsigned int j = i * msize; j < i * msize + msize; j++)
            matr->push_back(a[j]);
        for (unsigned int j = i * msize; j < i * msize + msize; j++)
            matr->push_back(b[j]);
    }
    for (unsigned int i = 0; i < msize; i++) {
        for (unsigned int j = i * msize; j < i * msize + msize; j++)
            matr->push_back(c[j]);
        for (unsigned int j = i * msize; j < i * msize + msize; j++)
            matr->push_back(d[j]);
    }
}

std::vector<double> toPowerOfTwoSize(const std::vector<double>& matr,
    unsigned int msize) {
    unsigned int power = 2;
    while (msize > power)
        power *= 2;
    std::vector<double> res;
    for (unsigned i = 0; i < msize; i++) {
        for (unsigned j = 0; j < msize; j++)
            res.push_back(matr[j + i * msize]);
        for (unsigned j = msize; j < power; j++)
            res.push_back(0);
    }
    for (unsigned i = msize; i < power; i++) {
        for (unsigned j = 0; j < power; j++)
            res.push_back(0);
    }
    return res;
}

std::vector<double> toPowerOfTwoSize(const std::vector<double>& matr,
    unsigned* power, unsigned int msize) {
    *power = 2;
    while (msize > *power)
        *power *= 2;
    unsigned tpow = *power;
    std::vector<double> res;
    for (unsigned i = 0; i < msize; i++) {
        for (unsigned j = 0; j < msize; j++)
            res.push_back(matr[j + i * msize]);
        for (unsigned j = msize; j < tpow; j++)
            res.push_back(0);
    }
    for (unsigned i = msize; i < tpow; i++) {
        for (unsigned j = 0; j < tpow; j++)
            res.push_back(0);
    }
    return res;
}

std::vector<double> matrixReduce(const std::vector<double>& matr,
    unsigned int msize) {
    std::vector<double> res(msize * msize);
    unsigned matrsize = static_cast<unsigned>(std::sqrt(matr.size()));

    for (unsigned i = 0; i < msize; i++)
        for (unsigned j = 0; j < msize; j++) {
            res[i * msize + j] = matr[i * matrsize + j];
        }

    return res;
}



std::vector<double> sMult_NoCastToPowerOfTwo(const std::vector<double>& a_,
    const std::vector<double>& b_, unsigned int msize) {
    std::vector<double> res;

    std::vector<double> a11, a12, a21, a22;
    std::vector<double> b11, b12, b21, b22;

    splitMatrix(a_, &a11, &a12, &a21, &a22, msize);
    splitMatrix(b_, &b11, &b12, &b21, &b22, msize);

    unsigned int split_msize = msize / 2;

    std::vector<double> p1, p2, p3, p4, p5, p6, p7;


    if (a11.size() > 256) {
        p1 = sMult_NoCastToPowerOfTwo(sum(a11, a22, split_msize),
        sum(b11, b22, split_msize), split_msize);
        p2 = sMult_NoCastToPowerOfTwo(sum(a21, a22, split_msize),
        b11, split_msize);
        p3 = sMult_NoCastToPowerOfTwo(a11, diff(b12, b22, split_msize),
        split_msize);
        p4 = sMult_NoCastToPowerOfTwo(a22, diff(b21, b11, split_msize),
        split_msize);
        p5 = sMult_NoCastToPowerOfTwo(sum(a11, a12, split_msize), b22,
        split_msize);
        p6 = sMult_NoCastToPowerOfTwo(diff(a21, a11, split_msize),
        sum(b11, b12, split_msize), split_msize);
        p7 = sMult_NoCastToPowerOfTwo(diff(a12, a22, split_msize),
        sum(b21, b22, split_msize), split_msize);
    } else {
        p1 = mMult(sum(a11, a22, split_msize), sum(b11, b22, split_msize),
        split_msize);
        p2 = mMult(sum(a21, a22, split_msize), b11, split_msize);
        p3 = mMult(a11, diff(b12, b22, split_msize), split_msize);
        p4 = mMult(a22, diff(b21, b11, split_msize), split_msize);
        p5 = mMult(sum(a11, a12, split_msize), b22, split_msize);
        p6 = mMult(diff(a21, a11, split_msize), sum(b11, b12, split_msize),
        split_msize);
        p7 = mMult(diff(a12, a22, split_msize), sum(b21, b22, split_msize),
        split_msize);
    }

    std::vector<double> c11, c12, c21, c22;

    c11 = sum(diff(sum(p1, p4, split_msize), p5, split_msize), p7,
    split_msize);
    c12 = sum(p3, p5, split_msize);
    c21 = sum(p2, p4, split_msize);
    c22 = sum(sum(diff(p1, p2, split_msize), p3, split_msize), p6,
    split_msize);

    mergeMatrix(&res, c11, c12, c21, c22, msize);

    return res;
}

std::vector<double> sMult(const std::vector<double>& a,
    const std::vector<double>& b, unsigned int msize) {
    unsigned tpow;
    std::vector<double> a_ = toPowerOfTwoSize(a, &tpow, msize);
    std::vector<double> b_ = toPowerOfTwoSize(b, msize);

    std::vector<double> res = sMult_NoCastToPowerOfTwo(a_, b_, tpow);

    return matrixReduce(res, msize);
}
