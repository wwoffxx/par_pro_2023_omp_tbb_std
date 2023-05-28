// Copyright 2023 Kryuchkov Vladimir

#include "../../../modules/task_4/kryuchkov_v_fox_algorithm_std/fox_algorithm.h"

#include <iostream>
#include <random>
#include <utility>
#include <cmath>
#include <vector>
#include <algorithm>

#include "../../../3rdparty/unapproved/unapproved.h"

std::vector<std::vector<double>> GetRandomMatrix(const int& size) {
  if (size <= 0) {
    throw "Wrong size matrix";
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1000.0);

  std::vector<std::vector<double>> res(size, std::vector<double>(size));
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      res[i][j] = dis(gen);
    }
  }
  return res;
}

std::vector<std::vector<double>> SimpleMultiplication(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {
  if (A.size() != B.size()) {
    throw "Different size";
  }
  if (A.size() <= 0 || B.size() <= 0) {
    throw "Size of matrix must be > 0";
  }

  size_t n = A.size();
  size_t m = B[0].size();
  std::vector<std::vector<double>> C(n, std::vector<double>(n, 0));

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      for (size_t k = 0; k < B.size(); ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return C;
}

std::vector<std::vector<double>> BlockMultiplication(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {
  if (A.size() != B.size()) {
    throw "Different size";
  }
  if (A.size() <= 0 || B.size() <= 0) {
    throw "Size of matrix must be > 0";
  }

  size_t n = A.size();
  size_t q = n / std::sqrt(n);
  size_t BlockSize = n / q;
  std::vector<std::vector<double>> C(n, std::vector<double>(n, 0));
  size_t EndA, EndB;
  for (size_t a = 0; a < n; a += BlockSize) {
    EndA = std::min(a + BlockSize, n);
    for (size_t b = 0; b < n; b += BlockSize) {
      EndB = std::min(b + BlockSize, n);
      for (size_t i = 0; i < n; i++) {
        for (size_t j = a; j < EndA; j++) {
          for (size_t k = b; k < EndB; k++) {
            C[i][j] += A[i][k] * B[k][j];
          }
        }
      }
    }
  }
  return C;
}

bool CompareMatrix(const std::vector<std::vector<double>>& A,
                   const std::vector<std::vector<double>>& B) {
  if (A.size() != B.size()) {
    throw "Different size";
  }
  if (A.size() <= 0 || B.size() <= 0) {
    throw "Size of matrix must be > 0";
  }

  bool eq = true;
  for (size_t i = 0; i < A.size(); i++) {
    for (size_t j = 0; j < A[0].size(); j++)
      if (std::fabs(A[i][j] - B[i][j]) >
          std::numeric_limits<double>::epsilon() * std::max(A[i][j], B[i][j]) *
              100)
        eq = false;
  }
  return eq;
}

std::vector<std::vector<double>> FoxParallel(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {
  if (A.size() != B.size()) {
    throw "Different size";
  }
  if (A.size() <= 0 || B.size() <= 0) {
    throw "Size of matrix must be > 0";
  }

  size_t n = A.size();
  size_t q = std::sqrt(std::thread::hardware_concurrency());
  size_t BlockSize = n / q;
  size_t nold = n;

  std::vector<std::vector<double>> EndA = A;
  std::vector<std::vector<double>> EndB = B;

  while (n % q != 0) {
    EndA.push_back(std::vector<double>(n, 0));
    EndB.push_back(std::vector<double>(n, 0));
    std::for_each(EndA.begin(), EndA.end(),
                  [](std::vector<double>& a) { a.push_back(0); });
    std::for_each(EndB.begin(), EndB.end(),
                  [](std::vector<double>& a) { a.push_back(0); });
    n++;
    BlockSize = n / q;
  }

  std::vector<std::vector<double>> C(n, std::vector<double>(n));

  auto f = [&](const int& x) {
    std::vector<std::vector<double>> A1(BlockSize), B1(BlockSize),
        tmp(BlockSize, std::vector<double>(BlockSize, 0));

    for (size_t n = 0; n < q; n++) {
      for (size_t m = 0; m < BlockSize; m++) {
        A1[m] = std::vector<double>(
            EndA[x / q * BlockSize + m].begin() + ((x / q + n) % q * BlockSize),
            EndA[x / q * BlockSize + m].begin() +
                ((x / q + n) % q * BlockSize + BlockSize));
        B1[m] = std::vector<double>(
            EndB[(x / q + n) % q * BlockSize + m].begin() + (x % q * BlockSize),
            EndB[(x / q + n) % q * BlockSize + m].begin() +
                (x % q * BlockSize + BlockSize));
      }
      for (size_t i = 0; i < BlockSize; i++) {
        for (size_t j = 0; j < BlockSize; j++) {
          for (size_t k = 0; k < BlockSize; k++)
            tmp[i][j] += A1[i][k] * B1[k][j];
        }
      }
    }

    for (size_t i = 0; i < BlockSize; i++) {
      for (size_t j = 0; j < BlockSize; j++) {
        C[i + x / q * BlockSize][j + x % q * BlockSize] = tmp[i][j];
      }
    }
  };

  std::vector<std::thread> threads(q * q);
  for (size_t i = 0; i < threads.size(); i++) {
    threads[i] = std::thread(f, i);
  }
  for (size_t i = 0; i < threads.size(); i++) {
    threads[i].join();
  }
  if (n != nold) {
    std::for_each(C.begin(), C.end(),
                  [&](std::vector<double>& a) { a.resize(nold); });
    C.resize(nold);
  }
  return C;
}
