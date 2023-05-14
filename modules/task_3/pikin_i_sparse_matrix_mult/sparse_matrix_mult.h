// Copyright 2023 Pikin Ilya
#ifndef MODULES_TASK_3_PIKIN_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_
#define MODULES_TASK_3_PIKIN_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_

#include <omp.h>
#include <tbb/tbb.h>
#include <set>
#include <ctime>
#include <vector>
#include <string>
#include <random>
#include <complex>
#include <iostream>


const double EPSILON = 0.00001;

class CRSMatrix {
 public:
  int n;
  int nz;

  std::vector<std::complex<double>> value;
  std::vector<int> column;
  std::vector<int> rowIndex;

  CRSMatrix() : n(0), nz(0) {}
  CRSMatrix(const CRSMatrix&) = default;
  explicit CRSMatrix(const std::vector<std::vector<std::complex<double>>>& M);
  CRSMatrix(int n, int nz, const std::vector<std::complex<double>>& v,
            const std::vector<int>& c, const std::vector<int>& rI);

  CRSMatrix& operator=(const CRSMatrix&) = default;
  bool operator==(const CRSMatrix& M) const;

  void printData();
  void printAsMatrix();
};

class CRSMatrixMultiplicator {
  const CRSMatrix& A;
  const CRSMatrix& BT;
  std::vector<std::vector<int>>* pColumns;
  std::vector<std::vector<std::complex<double>>>* pValues;
  std::vector<int>* pRowIndex;

 public:
  CRSMatrixMultiplicator(const CRSMatrix& A_, const CRSMatrix& BT_,
   std::vector<std::vector<int>>* pColumns_,
   std::vector<std::vector<std::complex<double>>>* pValues_,
   std::vector<int>* pRowIndex_);

  void operator()(const tbb::blocked_range<int>& range) const;
};

CRSMatrix getTransposed(const CRSMatrix& A);
CRSMatrix getRandCRSMatrix(int n, int cntInRow);
CRSMatrix getProductSeq(const CRSMatrix& A, const CRSMatrix& B);
CRSMatrix getProductOMP(const CRSMatrix& A, const CRSMatrix& B);
CRSMatrix getProductTBB(const CRSMatrix& A, const CRSMatrix& B);

#endif  // MODULES_TASK_3_PIKIN_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_
