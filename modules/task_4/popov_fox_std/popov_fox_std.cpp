// Copyright 2023 Popov Andrey
#include <vector>
#include <string>
#include <utility>
#include <random>
#include <cmath>
#include <iostream>
#include "../../../modules/task_4/popov_fox_std/popov_fox_std.h"
#include "../../../3rdparty/unapproved/unapproved.h"

Matrix getrandM(const int& num) {
  if (num <= 0) {
    throw std::exception();
  }
  std::random_device rand_dev;
  std::mt19937 generic(rand_dev());
  std::uniform_real_distribution<> distr(0, 100);

  Matrix result(num, std::vector<double>(num));
  for (int k = 0; k < num; ++k) {
    for (int l = 0; l < num; ++l) {
      result[k][l] = distr(generic);
    }
  }
  return result;
}

Matrix artlessmultiply(const Matrix& M1, const Matrix& M2) {
  if (M1[0].size() != M2.size()) throw std::exception();

  size_t x = M1.size();
  size_t y = M2[0].size();
  Matrix result(x, std::vector<double>(x));

  for (size_t l = 0; l < x; ++l) {
    for (size_t t = 0; t < y; ++t) {
      result[l][t] = 0;
      for (size_t k = 0; k < M2.size(); ++k) {
        result[l][t] += M1[l][k] * M2[k][t];
      }
    }
  }
  return result;
}

Matrix modularmultiply(const Matrix& M1, const Matrix& M2) {
  if (!isSquare(M1) || !isSquare(M2) || M1.size() != M2.size())
    throw std::logic_error("Matrix must be square");
  size_t X = M1.size();
  size_t quadr = X / std::sqrt(X);
  size_t block_size = X / quadr;
  Matrix result(X, std::vector<double>(X));

  for (size_t ll = 0; ll < X; ll += block_size) {
    for (size_t kk = 0; kk < X; kk += block_size) {
      for (size_t t = 0; t < X; ++t) {
        for (size_t l = ll; l < std::min(ll + block_size, X); ++l) {
          for (size_t k = kk; k < std::min(kk + block_size, X); ++k) {
            result[t][l] += M1[t][k] * M2[k][l];
          }
        }
      }
    }
  }

  return result;
}

bool matrixchecking(const Matrix& M1, const Matrix& M2) {
  if (M1.size() != M2.size() || M1[0].size() != M2[0].size())
    throw std::logic_error("Matrixes are different");
  bool isequival = true;
  for (size_t k = 0; k < M1.size() && isequival; ++k) {
    for (size_t l = 0; l < M1[0].size(); ++l)
      if (!doublechecking(M1[k][l], M2[k][l])) {
        std::cout << M1[k][l] << " " << M2[k][l] << std::endl;
        isequival = false;
        break;
      }
  }
  return isequival;
}

Matrix algorhythm_fox_parallel(const Matrix& M1, const Matrix& M2) {
  if (!isSquare(M1) || !isSquare(M2) || M1.size() != M2.size())
    throw std::logic_error("Matrix should be squared");
  auto cnt_threads = std::thread::hardware_concurrency();

  size_t X = M1.size();
  size_t quadre = std::sqrt(cnt_threads);
  size_t block_size = X / quadre;

  auto M1_clone = M1;
  auto M2_clone = M2;

  auto old_X = X;
  while (X % quadre != 0) {
    M1_clone.push_back(std::vector<double>(X, 0));
    M2_clone.push_back(std::vector<double>(X, 0));
    std::for_each(M1_clone.begin(), M1_clone.end(),
                  [](std::vector<double>& a) { a.push_back(0); });
    std::for_each(M2_clone.begin(), M2_clone.end(),
                  [](std::vector<double>& a) { a.push_back(0); });
    X++;
    block_size = X / quadre;
  }

  Matrix res(X, std::vector<double>(X));

  auto bd = [&](const int& id) {
    auto thread_i = id / quadre;
    auto thread_j = id % quadre;

    Matrix M(block_size), N(block_size),
        Z(block_size, std::vector<double>(block_size, 0));

    for (size_t step = 0; step < quadre; ++step) {
      auto k_bar = (thread_i + step) % quadre;
      for (size_t k = 0; k < block_size; ++k) {
        M[k] =
            std::vector<double>(M1_clone[thread_i * block_size + k].begin() +
                                    (k_bar * block_size),
                                M1_clone[thread_i * block_size + k].begin() +
                                    (k_bar * block_size + block_size));
        N[k] = std::vector<double>(M2_clone[k_bar * block_size + k].begin() +
                                       (thread_j * block_size),
                                   M2_clone[k_bar * block_size + k].begin() +
                                       (thread_j * block_size + block_size));
      }
      for (size_t t = 0; t < block_size; ++t) {
        for (size_t l = 0; l < block_size; ++l) {
          for (size_t kk = 0; kk < block_size; ++kk)
            Z[t][l] += M[t][kk] * N[kk][l];
        }
      }
    }

    for (size_t t = 0; t < block_size; ++t) {
      for (size_t l = 0; l < block_size; ++l) {
        auto res_i = t + thread_i * block_size;
        auto res_j = l + thread_j * block_size;
        res[res_i][res_j] = Z[t][l];
      }
    }
  };

  std::vector<std::thread> threads(quadre * quadre);
  for (size_t t = 0; t < threads.size(); ++t) {
    threads[t] = std::thread(bd, t);
  }
  for (size_t l = 0; l < threads.size(); ++l) {
    threads[l].join();
  }
  if (X != old_X) {
    std::for_each(res.begin(), res.end(),
                  [&](std::vector<double>& a) { a.resize(old_X); });
    res.resize(old_X);
  }
  return res;
}
