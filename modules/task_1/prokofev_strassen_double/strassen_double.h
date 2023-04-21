// Copyright 2023 Prokofev Denis
#ifndef MODULES_TASK_1_PROKOFEV_STRASSEN_DOUBLE_STRASSEN_DOUBLE_H_
#define MODULES_TASK_1_PROKOFEV_STRASSEN_DOUBLE_STRASSEN_DOUBLE_H_

#include <vector>

std::vector<double> rndMat(int  msize);
std::vector<double> mMult(const std::vector<double>& a,
    const std::vector<double>& b, unsigned int msize);
std::vector<double> sMult(const std::vector<double>& a,
    const std::vector<double>& b, unsigned int msize);
std::vector<double> sMult_lst(const std::vector<double>& a,
    const std::vector<double>& b, unsigned int msize);
std::vector<double> sum(const std::vector<double>& a,
    const std::vector<double>& b, unsigned int msize);
std::vector<double> diff(const std::vector<double>& a,
    const std::vector<double>& b, unsigned int msize);
void splitMatrix(const std::vector<double>& matr,
    std::vector<double>* a,
    std::vector<double>* b, std::vector<double>* c,
    std::vector<double>* d, unsigned int msize);
void mergeMatrix(std::vector<double>* matr, const std::vector<double>& a,
    const std::vector<double>& b, const std::vector<double>& c,
    const std::vector<double>& d, unsigned int msize);
std::vector<double> toPowerOfTwoSize(const std::vector<double>& matr,
    unsigned* power, unsigned int msize);
std::vector<double> toPowerOfTwoSize(const std::vector<double>& matr,
    unsigned int msize);
std::vector<double> matrixReduce(const std::vector<double>& matr,
    unsigned int msize);

#endif  // MODULES_TASK_1_PROKOFEV_STRASSEN_DOUBLE_STRASSEN_DOUBLE_H_
