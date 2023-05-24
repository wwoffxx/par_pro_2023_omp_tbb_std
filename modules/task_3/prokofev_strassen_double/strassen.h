// Copyright 2023 Prokofev Denis
#ifndef MODULES_TASK_3_PROKOFEV_STRASSEN_DOUBLE_STRASSEN_H
#define MODULES_TASK_3_PROKOFEV_STRASSEN_DOUBLE_STRASSEN_H

#include <vector>

std::vector<double> rndMat(int  sz);
std::vector<double> rMult(const std::vector<double> &a, const std::vector<double> &b, unsigned int sz);
std::vector<double> sMult_tbb(const std::vector<double> &a,
                                               const std::vector<double> &b, unsigned int sz);
std::vector<double> sMult_NoTwo(const std::vector<double>& a,
                                                              const std::vector<double>& b, unsigned int sz);
std::vector<double> sum(const std::vector<double> &a, const std::vector<double> &b, unsigned int sz);
std::vector<double> diff(const std::vector<double> &a, const std::vector<double> &b, unsigned int sz);
void splitMatrix(const std::vector<double> &mtx, std::vector<double> *a,
                 std::vector<double> *b, std::vector<double> *c, std::vector<double> *d, unsigned int sz);
void mergeMatrix(std::vector<double> *mtx, const std::vector<double> &a,
                 const std::vector<double> &b, const std::vector<double> &c,
                 const std::vector<double> &d, unsigned int sz);
std::vector<double> toPowerOfTwoSize(const std::vector<double>& mtx, unsigned* power, unsigned int sz);
std::vector<double> toPowerOfTwoSize(const std::vector<double>& mtx, unsigned int sz);
std::vector<double> matrixReduce(const std::vector<double>& mtx, unsigned int sz);

#endif  // MODULES_TASK_3_PROKOFEV_STRASSEN_DOUBLE_STRASSEN_H
