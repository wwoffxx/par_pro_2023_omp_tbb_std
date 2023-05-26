// Copyright 2023 Nikitin Aleksandr
#ifndef MODULES_TASK_3_NIKITIN_A_STRASSEN_TBB_STRASSEN_TBB_H_
#define MODULES_TASK_3_NIKITIN_A_STRASSEN_TBB_STRASSEN_TBB_H_

#include <string>
#include <vector>

void naive_mult(double* a, double* b, double* c, int size);
void get_p1(double* a11, double* a22, double* res1, double* b11, double* b22,
            double* res2, double* slice, int size);
void get_p2(double* a21, double* a22, double* res1, double* b11, double* slice,
            int size);
void get_p3(double* a11, double* res1, double* b12, double* b22, double* slice,
            int size);
void get_p4(double* a22, double* res1, double* b21, double* b11, double* slice,
            int size);
void get_p5(double* a11, double* a12, double* res1, double* b22, double* slice,
            int size);
void get_p6(double* a21, double* a11, double* res1, double* b11, double* b12,
            double* res2, double* slice, int size);
void get_p7(double* a12, double* a22, double* res1, double* b21, double* b22,
            double* res2, double* slice, int size);
bool is_exp_of_2(int n);
void strassen(double* a, double* b, double* c, int size);

#endif  // MODULES_TASK_3_NIKITIN_A_STRASSEN_TBB_STRASSEN_TBB_H_
