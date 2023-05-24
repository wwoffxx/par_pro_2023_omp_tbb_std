// Copyright 2023 Prokofev Denis

#include <../../../modules/task_3/prokofev_strassen_double/strassen.h>
#include <tbb/tbb.h>
#include <random>
#include <ctime>
#include <vector>

std::vector<double> rndMat(int siz) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<double> vec(siz*siz);
  for (int i = 0; i < siz*siz; i++) {
    vec[i] = gen() % 9 + 1;
  }
  return vec;
}

std::vector<double> rMult(const std::vector<double>& a, const std::vector<double>& b, unsigned int siz) {
  std::vector<double> rs(siz* siz);
  for (unsigned int i = 0; i < siz; i++)
    for (unsigned int j = 0; j < siz; j++) {
      for (unsigned int k = 0; k < siz; k++)
        rs[j + i * siz] += a[i * siz + k] * b[j + k * siz];
    }
  return rs;
}

std::vector<double> sum(const std::vector<double>& a, const std::vector<double>& b, unsigned int siz) {
  unsigned int size = siz * siz;
  std::vector<double> rs(size);
  for (unsigned int i = 0; i < size; i++) {
    rs[i] = a[i] + b[i];
  }
  return rs;
}

std::vector<double> diff(const std::vector<double>& a, const std::vector<double>& b, unsigned int siz) {
  unsigned int size = siz * siz;
  std::vector<double> rs(size);
  for (unsigned int i = 0; i < size; i++) {
    rs[i] = a[i] - b[i];
  }
  return rs;
}

void splitMatrix(const std::vector<double> &mat, std::vector<double> *a,
                 std::vector<double> *b, std::vector<double> *c, std::vector<double> *d, unsigned int size) {
  unsigned int siz = size / 2;
  for (unsigned int i = 0; i < siz; i++) {
    for (unsigned int j = i * 2 * siz; j < i * 2 * siz + siz; j++)
      a->push_back(mat[j]);
    for (unsigned int j = i * 2 * siz + siz; j < i * 2 * siz + 2 * siz; j++)
      b->push_back(mat[j]);
  }
  for (unsigned int i = siz; i < 2*siz; i++) {
    for (unsigned int j = i * 2 * siz; j < i * 2 * siz + siz; j++)
      c->push_back(mat[j]);
    for (unsigned int j = i * 2 * siz + siz; j < i * 2 * siz + 2 * siz; j++)
      d->push_back(mat[j]);
  }
}

void mergeMatrix(std::vector<double> *mat, const std::vector<double> &a, const std::vector<double> &b,
                 const std::vector<double> &c, const std::vector<double> &d, unsigned int size) {
  unsigned int siz = size / 2;
  for (unsigned int i = 0; i < siz; i++) {
    for (unsigned int j = i * siz; j < i * siz + siz; j++)
      mat->push_back(round(a[j] * 100) / 100);
    for (unsigned int j = i * siz; j < i * siz + siz; j++)
      mat->push_back(round(b[j] * 100) / 100);
  }
  for (unsigned int i = 0; i < siz; i++) {
    for (unsigned int j = i * siz; j < i * siz + siz; j++)
      mat->push_back(round(c[j] * 100) / 100);
    for (unsigned int j = i * siz; j < i * siz + siz; j++)
      mat->push_back(round(d[j] * 100) / 100);
  }
}

std::vector<double> toPowerOfTwoSize(const std::vector<double>& mat, unsigned int siz) {
  unsigned int pwr = 2;
  while (siz > pwr)
    pwr *= 2;
  std::vector<double> rs;
  for (unsigned i = 0; i < siz; i++) {
    for (unsigned j = 0; j < siz; j++)
      rs.push_back(mat[j + i * siz]);
    for (unsigned j = siz; j < pwr; j++)
      rs.push_back(0);
  }
  for (unsigned i = siz; i < pwr; i++) {
    for (unsigned j = 0; j < pwr; j++)
      rs.push_back(0);
  }
  return rs;
}

std::vector<double> toPowerOfTwoSize(const std::vector<double> &mat, unsigned* pwr, unsigned int siz) {
  *pwr = 2;
  while (siz > *pwr)
    *pwr *= 2;
  unsigned tpow = *pwr;
  std::vector<double> rs;
  for (unsigned i = 0; i < siz; i++) {
    for (unsigned j = 0; j < siz; j++)
      rs.push_back(mat[j + i * siz]);
    for (unsigned j = siz; j < tpow; j++)
      rs.push_back(0);
  }
  for (unsigned i = siz; i < tpow; i++) {
    for (unsigned j = 0; j < tpow; j++)
      rs.push_back(0);
  }
  return rs;
}

std::vector<double> matrixReduce(const std::vector<double>& mat, unsigned int siz) {
  std::vector<double> rs(siz*siz);
  unsigned matsize = static_cast<unsigned>(std::sqrt(mat.size()));

  for (unsigned i = 0; i < siz; i++)
    for (unsigned j = 0; j < siz; j++) {
      rs[i * siz + j] = mat[i * matsize + j];
    }

  return rs;
}

std::vector<double> sMult_tbb(const std::vector<double>& a,
                                           const std::vector<double>& b, unsigned int siz) {
  unsigned tpow;
  std::vector<double> a_ = toPowerOfTwoSize(a, &tpow, siz);
  std::vector<double> b_ = toPowerOfTwoSize(b, siz);
  std::vector<double> rs;

  rs = sMult_NoTwo(a_, b_, tpow);

  return matrixReduce(rs, siz);
}

std::vector<double> sMult_NoTwo(const std::vector<double>& a_,
                    const std::vector<double>& b_, unsigned int siz) {
  std::vector<double> rs;

  std::vector<double> a11, a12, a21, a22;
  std::vector<double> b11, b12, b21, b22;
  std::vector<double> p1, p2, p3, p4, p5, p6, p7;

  unsigned int split_sz = siz / 2;

  splitMatrix(a_, &a11, &a12, &a21, &a22, siz);
  splitMatrix(b_, &b11, &b12, &b21, &b22, siz);

  tbb::task_group group;

  if (a11.size() > 256) {
    group.run([&] {
      p1 = sMult_NoTwo(sum(a11, a22, split_sz),
        sum(b11, b22, split_sz), split_sz);
    });
    group.run([&] {
      p2 = sMult_NoTwo(sum(a21, a22, split_sz), b11, split_sz);
    });
    group.run([&] {
      p3 = sMult_NoTwo(a11, diff(b12, b22, split_sz), split_sz);
    });
    group.run([&] {
      p4 = sMult_NoTwo(a22, diff(b21, b11, split_sz), split_sz);
    });
    group.run([&] {
      p5 = sMult_NoTwo(sum(a11, a12, split_sz),
          b22, split_sz);
    });
    group.run([&] {
      p6 = sMult_NoTwo(diff(a21, a11, split_sz),
        sum(b11, b12, split_sz), split_sz);
    });
    group.run([&] {
      p7 = sMult_NoTwo(diff(a12, a22, split_sz),
        sum(b21, b22, split_sz), split_sz);
    });
    group.wait();
  } else {
    p1 = rMult(sum(a11, a22, split_sz), sum(b11, b22, split_sz), split_sz);
    p2 = rMult(sum(a21, a22, split_sz), b11, split_sz);
    p3 = rMult(a11, diff(b12, b22, split_sz), split_sz);
    p4 = rMult(a22, diff(b21, b11, split_sz), split_sz);
    p5 = rMult(sum(a11, a12, split_sz), b22, split_sz);
    p6 = rMult(diff(a21, a11, split_sz), sum(b11, b12, split_sz), split_sz);
    p7 = rMult(diff(a12, a22, split_sz), sum(b21, b22, split_sz), split_sz);
  }

  std::vector<double> c11, c12, c21, c22;

  c11 = sum(diff(sum(p1, p4, split_sz), p5, split_sz), p7, split_sz);
  c12 = sum(p3, p5, split_sz);
  c21 = sum(p2, p4, split_sz);
  c22 = sum(sum(diff(p1, p2, split_sz), p3, split_sz), p6, split_sz);

  mergeMatrix(&rs, c11, c12, c21, c22, siz);

  return rs;
}
