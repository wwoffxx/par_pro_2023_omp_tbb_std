// Copyright 2023 Popov Andrey
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "../../../modules/task_1/Popov_Fox_matrix/Popov_Fox_matrix.h"

matrix simpleMult(const matrix& X, const matrix& Y) {
  if (X[0].size() != Y.size()) throw "Different size";
  int N = X.size();
  int M = Y[0].size();
  matrix C(N, std::vector<double>(N, 0));
  int sz = Y.size();
  for (int k = 0; k < N; k++) {
    for (int l = 0; l < M; l++) {
      for (int t = 0; t < sz; t++) {
        C[k][l] += X[k][t] * Y[t][l];
      }
    }
  }
  return C;
}

matrix foxMult(const matrix& X, const matrix& Y, const int& sizeb) {
  if (X[0].size() != Y.size()) throw "Different size";
  int n = X.size();
  if (sizeb > n) throw "block size is larger than matrix size";
  matrix C(n, std::vector<double>(n, 0));
  int endX, endY;
  for (int a = 0; a < n; a += sizeb) {
    endX = std::min(a + sizeb, n);
    for (int b = 0; b < n; b += sizeb) {
      endY = std::min(b + sizeb, n);
      for (int i = 0; i < n; i++) {
        for (int j = a; j < endX; j++) {
          for (int k = b; k < endY; k++) {
            C[i][j] += X[i][k] * Y[k][j];
          }
        }
      }
    }
  }

  return C;
}

matrix randMatrix(const int& cnt) {
  if (cnt <= 0) {
    throw "Wrong size matrix";
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1000.0);
  matrix mat(cnt, std::vector<double>(cnt));
  for (int k = 0; k < cnt; k++) {
    for (int l = 0; l < cnt; l++) {
      mat[k][l] = dis(gen);
    }
  }
  return mat;
}
