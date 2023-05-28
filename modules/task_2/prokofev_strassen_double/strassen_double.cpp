  // Copyright 2023 Prokofev Denis

#include <../../../modules/task_2/prokofev_strassen_double/strassen_double.h>

#include <omp.h>
#include <random>
#include <ctime>
#include <vector>

std::vector<double> rndMat(int sz) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<double> vec(sz*sz);
  for (int i = 0; i < sz*sz; i++) {
    vec[i] = gen() % 9 + 1;
  }
  return vec;
}

std::vector<double> mMult(const std::vector<double>& a, const std::vector<double>& b, unsigned int sz) {
  std::vector<double> res(sz* sz);
  for (unsigned int i = 0; i < sz; i++)
    for (unsigned int j = 0; j < sz; j++) {
      for (unsigned int k = 0; k < sz; k++)
        res[j + i * sz] += a[i * sz + k] * b[j + k * sz];
    }
  return res;
}

std::vector<double> sum(const std::vector<double>& a, const std::vector<double>& b, unsigned int sz) {
  unsigned int size = sz * sz;
  std::vector<double> res(size);
  for (unsigned int i = 0; i < size; i++) {
    res[i] = a[i] + b[i];
  }
  return res;
}

std::vector<double> diff(const std::vector<double>& a, const std::vector<double>& b, unsigned int sz) {
  unsigned int size = sz * sz;
  std::vector<double> res(size);
  for (unsigned int i = 0; i < size; i++) {
    res[i] = a[i] - b[i];
  }
  return res;
}

void splitMatrix(const std::vector<double> &mtx, std::vector<double> *a,
                 std::vector<double> *b, std::vector<double> *c, std::vector<double> *d, unsigned int size) {
  unsigned int sz = size / 2;
  for (unsigned int i = 0; i < sz; i++) {
    for (unsigned int j = i * 2 * sz; j < i * 2 * sz + sz; j++)
      a->push_back(mtx[j]);
    for (unsigned int j = i * 2 * sz + sz; j < i * 2 * sz + 2 * sz; j++)
      b->push_back(mtx[j]);
  }
  for (unsigned int i = sz; i < 2*sz; i++) {
    for (unsigned int j = i * 2 * sz; j < i * 2 * sz + sz; j++)
      c->push_back(mtx[j]);
    for (unsigned int j = i * 2 * sz + sz; j < i * 2 * sz + 2 * sz; j++)
      d->push_back(mtx[j]);
  }
}

void mergeMatrix(std::vector<double> *mtx, const std::vector<double> &a, const std::vector<double> &b,
                 const std::vector<double> &c, const std::vector<double> &d, unsigned int size) {
  unsigned int sz = size / 2;
  for (unsigned int i = 0; i < sz; i++) {
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx->push_back(round(a[j]*100)/100);
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx->push_back(round(b[j]*100)/100);
  }
  for (unsigned int i = 0; i < sz; i++) {
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx->push_back(round(c[j]*100)/100);
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx->push_back(round(d[j]*100)/100);
  }
}

std::vector<double> toPowerOfTwoSize(const std::vector<double>& mtx, unsigned int sz) {
  unsigned int power = 2;
  while (sz > power)
    power *= 2;
  std::vector<double> res;
  for (unsigned i = 0; i < sz; i++) {
    for (unsigned j = 0; j < sz; j++)
      res.push_back(mtx[j + i * sz]);
    for (unsigned j = sz; j < power; j++)
      res.push_back(0);
  }
  for (unsigned i = sz; i < power; i++) {
    for (unsigned j = 0; j < power; j++)
      res.push_back(0);
  }
  return res;
}

std::vector<double> toPowerOfTwoSize(const std::vector<double> &mtx, unsigned* power, unsigned int sz) {
  *power = 2;
  while (sz > *power)
    *power *= 2;
  unsigned tpow = *power;
  std::vector<double> res;
  for (unsigned i = 0; i < sz; i++) {
    for (unsigned j = 0; j < sz; j++)
      res.push_back(mtx[j + i * sz]);
    for (unsigned j = sz; j < tpow; j++)
      res.push_back(0);
  }
  for (unsigned i = sz; i < tpow; i++) {
    for (unsigned j = 0; j < tpow; j++)
      res.push_back(0);
  }
  return res;
}

std::vector<double> matrixReduce(const std::vector<double>& mtx, unsigned int sz) {
  std::vector<double> res(sz*sz);
  unsigned mtxsize = static_cast<unsigned>(std::sqrt(mtx.size()));

  for (unsigned i = 0; i < sz; i++)
    for (unsigned j = 0; j < sz; j++) {
      res[i * sz + j] = mtx[i * mtxsize + j];
    }

  return res;
}

std::vector<double> sMult_NoCastToPowerOfTwo(const std::vector<double>& a,
                                           const std::vector<double>& b, unsigned int sz) {
  unsigned tpow;
  std::vector<double> a_ = toPowerOfTwoSize(a, &tpow, sz);
  std::vector<double> b_ = toPowerOfTwoSize(b, sz);
  std::vector<double> res;

  res = sMult(a_, b_, tpow);

  return matrixReduce(res, sz);
}

std::vector<double> sMult(const std::vector<double>& a_,
                    const std::vector<double>& b_, unsigned int sz) {
  std::vector<double> res;

    std::vector<double> a11, a12, a21, a22;
    std::vector<double> b11, b12, b21, b22;
    std::vector<double> p1, p2, p3, p4, p5, p6, p7;

    unsigned int split_sz = sz / 2;

    splitMatrix(a_, &a11, &a12, &a21, &a22, sz);
    splitMatrix(b_, &b11, &b12, &b21, &b22, sz);

  if (a11.size() > 256) {
    #pragma omp parallel
    {
    #pragma omp sections
      {
        #pragma omp section
          p1 = sMult(sum(a11, a22, split_sz),
               sum(b11, b22, split_sz), split_sz);
        #pragma omp section
          p2 = sMult(sum(a21, a22, split_sz), b11, split_sz);
        #pragma omp section
          p3 = sMult(a11, diff(b12, b22, split_sz), split_sz);
        #pragma omp section
          p4 = sMult(a22, diff(b21, b11, split_sz), split_sz);
        #pragma omp section
          p5 = sMult(sum(a11, a12, split_sz),
                b22, split_sz);
        #pragma omp section
          p6 = sMult(diff(a21, a11, split_sz),
               sum(b11, b12, split_sz), split_sz);
        #pragma omp section
          p7 = sMult(diff(a12, a22, split_sz),
               sum(b21, b22, split_sz), split_sz);
      }
    }
  } else {
    p1 = mMult(sum(a11, a22, split_sz), sum(b11, b22, split_sz), split_sz);
    p2 = mMult(sum(a21, a22, split_sz), b11, split_sz);
    p3 = mMult(a11, diff(b12, b22, split_sz), split_sz);
    p4 = mMult(a22, diff(b21, b11, split_sz), split_sz);
    p5 = mMult(sum(a11, a12, split_sz), b22, split_sz);
    p6 = mMult(diff(a21, a11, split_sz), sum(b11, b12, split_sz), split_sz);
    p7 = mMult(diff(a12, a22, split_sz), sum(b21, b22, split_sz), split_sz);
  }

  std::vector<double> c11, c12, c21, c22;

  c11 = sum(diff(sum(p1, p4, split_sz), p5, split_sz), p7, split_sz);
  c12 = sum(p3, p5, split_sz);
  c21 = sum(p2, p4, split_sz);
  c22 = sum(sum(diff(p1, p2, split_sz), p3, split_sz), p6, split_sz);

  mergeMatrix(&res, c11, c12, c21, c22, sz);

  return res;
}
