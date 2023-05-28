// Copyright 2023 Zanozin Danila
#include "../../../modules/task_3/zanozin_d_cannon_metod/cannon_metod.h"

Matrix CreateRandomMatrix(const int n) {
  if (n <= 0) throw std::invalid_argument("matrix size n should be positive");

  Matrix mat(n, std::vector<double>(n, 0));

  std::uniform_real_distribution<double> dis(0, 99);
  std::mt19937 gen;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      mat[i][j] = dis(gen);
    }
  }
  return mat;
}

void ExpectMatricesNear(const Matrix &A, const Matrix &B, size_t N) {
  if (A.size() != B.size())
    throw std::runtime_error("Matrices should have equal dimensions");

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      EXPECT_NEAR(A[i][j], B[i][j], 0.01);
    }
  }
}

Matrix MultMat(const Matrix &A, const Matrix &B, size_t N) {
  Matrix Result(N, std::vector<double>(N, 0.0));
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      for (size_t k = 0; k < N; ++k) {
        Result[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return Result;
}

Matrix SeqCannonMult(const Matrix &A, const Matrix &B, size_t blocksNum,
                     size_t blockSize, size_t N) {
  Matrix Result(N, std::vector<double>(N, 0.0));
  for (size_t ri = 0; ri < blocksNum * blocksNum; ri++) {
    Matrix Cij(blockSize, std::vector<double>(blockSize, 0.0));
    size_t iPos = ri / blocksNum;
    size_t jPos = ri % blocksNum;
    auto Apos = std::make_pair(iPos, (jPos + iPos) % blocksNum);
    auto Bpos = std::make_pair((jPos + iPos) % blocksNum, jPos);

    for (size_t p = 0; p < blocksNum; ++p) {
      for (size_t i = 0; i < blockSize; ++i) {
        for (size_t j = 0; j < blockSize; ++j) {
          for (size_t k = 0; k < blockSize; ++k) {
            size_t ai = Apos.first * blockSize;
            size_t bi = Bpos.first * blockSize;
            size_t aj = Apos.second * blockSize;
            size_t bj = Bpos.second * blockSize;
            Cij[i][j] += A[ai + i][aj + k] * B[bi + k][bj + j];
          }
        }
      }
      Apos.second = (Apos.second + 1) % blocksNum;
      Bpos.first = (Bpos.first + 1) % blocksNum;
    }
    for (size_t i = 0; i < blockSize; ++i) {
      for (size_t j = 0; j < blockSize; ++j) {
        Result[iPos * blockSize + i][jPos * blockSize + j] = Cij[i][j];
      }
    }
  }
  return Result;
}

Matrix TBBCannonMult(const Matrix &A, const Matrix &B, size_t n, size_t bs,
                     size_t s) {
  Matrix Result(s, std::vector<double>(s, 0.0));

  auto func = [&](const tbb::blocked_range<size_t> &range) {
    for (size_t ri = range.begin(); ri < range.end(); ri++) {
      Matrix Cij(bs, std::vector<double>(bs, 0.0));
      size_t iPos = ri / n;
      size_t jPos = ri % n;
      auto Apos = std::make_pair(iPos, (jPos + iPos) % n);
      auto Bpos = std::make_pair((jPos + iPos) % n, jPos);

      for (size_t p = 0; p < n; ++p) {
        for (size_t i = 0; i < bs; ++i) {
          for (size_t j = 0; j < bs; ++j) {
            for (size_t k = 0; k < bs; ++k) {
              size_t ai = Apos.first * bs;
              size_t bi = Bpos.first * bs;
              size_t aj = Apos.second * bs;
              size_t bj = Bpos.second * bs;
              Cij[i][j] += A[ai + i][aj + k] * B[bi + k][bj + j];
            }
          }
        }
        Apos.second = (Apos.second + 1) % n;
        Bpos.first = (Bpos.first + 1) % n;
      }
      for (size_t i = 0; i < bs; ++i) {
        for (size_t j = 0; j < bs; ++j) {
          Result[iPos * bs + i][jPos * bs + j] = Cij[i][j];
        }
      }
    }
  };

  tbb::parallel_for(tbb::blocked_range<size_t>(0, n * n), func);
  return Result;
}
