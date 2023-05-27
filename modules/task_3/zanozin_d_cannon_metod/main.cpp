// Copyright 2023 Zanozin Danila
#include "./cannon_metod.h"

TEST(KanonsMethodTBB, MultTest4x4) {
  size_t N = 4;
  size_t blocksNum = 2;
  size_t blockSize = 2;

  Matrix A, B, ResUsual, ResCannonTBB;
  A = CreateRandomMatrix(N);
  B = CreateRandomMatrix(N);

  ResUsual = MultMat(A, B, N);
  ResCannonTBB = TBBCannonMult(A, B, blocksNum, blockSize, N);

  ExpectMatricesNear(ResUsual, ResCannonTBB, N);
}

TEST(KanonsMethodTBB, MultTest16x16) {
  size_t N = 16;
  size_t blocksNum = 2;
  size_t blockSize = 8;

  Matrix A, B, ResUsual, ResCannonTBB;
  A = CreateRandomMatrix(N);
  B = CreateRandomMatrix(N);

  ResUsual = MultMat(A, B, N);
  ResCannonTBB = TBBCannonMult(A, B, blocksNum, blockSize, N);

  ExpectMatricesNear(ResUsual, ResCannonTBB, N);
}

TEST(KanonsMethodTBB, MultTest20x20) {
  size_t N = 20;
  size_t blocksNum = 2;
  size_t blockSize = 10;

  Matrix A, B, ResUsual, ResCannonTBB;
  A = CreateRandomMatrix(N);
  B = CreateRandomMatrix(N);

  ResUsual = MultMat(A, B, N);
  ResCannonTBB = TBBCannonMult(A, B, blocksNum, blockSize, N);

  ExpectMatricesNear(ResUsual, ResCannonTBB, N);
}

TEST(KanonsMethodTBB, MultTest32x32) {
  size_t N = 32;
  size_t blocksNum = 2;
  size_t blockSize = 16;

  Matrix A, B, ResUsual, ResCannonTBB;
  A = CreateRandomMatrix(N);
  B = CreateRandomMatrix(N);

  ResUsual = MultMat(A, B, N);
  ResCannonTBB = TBBCannonMult(A, B, blocksNum, blockSize, N);

  ExpectMatricesNear(ResUsual, ResCannonTBB, N);
}

TEST(KanonsMethodTBB, MultTest48x48) {
  size_t N = 48;
  size_t blocksNum = 4;
  size_t blockSize = 12;

  Matrix A, B, ResUsual, ResCannonTBB;
  A = CreateRandomMatrix(N);
  B = CreateRandomMatrix(N);

  ResUsual = MultMat(A, B, N);
  ResCannonTBB = TBBCannonMult(A, B, blocksNum, blockSize, N);

  ExpectMatricesNear(ResUsual, ResCannonTBB, N);
}
