// Copyright 2023 Binko Alexandr
#include "../../../modules/task_2/binko_a_kanon/kanon.h"

#include <omp.h>

#include <algorithm>
#include <random>
#include <vector>

void Matrix::toLeftSide(std::vector<std::vector<double>> *matr, int pos,
                        int block_count, int skew) {
  std::vector<std::vector<double>> tmp_matr;

  for (int i = 0; i < skew; ++i) {
    std::vector<double> vec(skew);
    tmp_matr.push_back(vec);
    for (int j = 0; j < skew; ++j) {
      tmp_matr[i][j] = matr->at(i + skew * pos).at(j);
    }
  }
  for (int k = 0; k < block_count - 1; ++k) {
    for (int i = 0; i < skew; ++i) {
      for (int j = 0; j < skew; ++j) {
        matr->at(i + skew * pos).at(j + skew * k) =
            matr->at(i + skew * pos).at(j + skew * (k + 1));
      }
    }
  }
  for (int i = 0; i < skew; ++i) {
    for (int j = 0; j < skew; ++j) {
      matr->at(i + skew * pos).at(j + skew * (block_count - 1)) =
          tmp_matr[i][j];
    }
  }
}

void Matrix::shiftUp(std::vector<std::vector<double>> *matr, int pos,
                     int block_count, int skew) {
  std::vector<std::vector<double>> tmp_matr;

  for (int i = 0; i < skew; ++i) {
    std::vector<double> vec(skew);
    tmp_matr.push_back(vec);
    for (int j = 0; j < skew; ++j) {
      tmp_matr[i][j] = matr->at(i).at(j + skew * pos);
    }
  }
  for (int i = 0; i < block_count - 1; ++i) {
    for (int j = 0; j < skew; ++j) {
      for (int k = 0; k < skew; ++k) {
        matr->at(j + skew * i).at(k + skew * pos) =
            matr->at(j + skew * (i + 1)).at(k + skew * pos);
      }
    }
  }
  for (int i = 0; i < skew; ++i) {
    for (int j = 0; j < skew; ++j) {
      matr->at(i + skew * (block_count - 1)).at(j + skew * pos) =
          tmp_matr[i][j];
    }
  }
}

void Matrix::mutiplyByBlock(std::vector<std::vector<double>> block1,
                            std::vector<std::vector<double>> block2,
                            std::vector<std::vector<double>> *res_block,
                            int shift_l, int shift_r, int skew) {
  for (int i = 0; i < skew; i++)
    for (int j = 0; j < skew; j++)
      for (int k = 0; k < skew; k++)
        res_block->at(i + skew * shift_l).at(j + skew * shift_r) +=
            block1[i + skew * shift_l][skew * shift_r + k] *
            block2[k + skew * shift_l][j + skew * shift_r];
}

void Matrix::fillNewMatrix(double num) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      matrix[i][j] = i * num;
    }
  }
}

std::vector<std::vector<double>> Matrix::seqKanonAlg(
    Matrix matrix2, std::vector<std::vector<double>> res_matrix, int block_size,
    int block_count) {
  for (int i = 1; i < block_count; ++i) {
    for (int j = 0; j < i; ++j) {
      toLeftSide(&this->matrix, i, block_count, block_size);
      shiftUp(&matrix2.matrix, i, block_count, block_size);
    }
  }
  for (int i = 0; i < block_count; ++i) {
    for (int j = 0; j < block_count; ++j) {
      for (int k = 0; k < block_count; ++k) {
        mutiplyByBlock(this->matrix, matrix2.matrix, &res_matrix, j, k,
                       block_size);
      }
    }
    for (int l = 0; l < block_count; ++l) {
      toLeftSide(&this->matrix, l, block_count, block_size);
      shiftUp(&matrix2.matrix, l, block_count, block_size);
    }
  }
  return res_matrix;
}

std::vector<std::vector<double>> Matrix::ompKanonAlg(
    Matrix matrix2, int thread_nums,
    std::vector<std::vector<double>> res_matrix, int block_size,
    int block_count) {
  int i, j, k, l;
  int num_threads = thread_nums;
#pragma omp parallel shared(matrix2) private(i, j)
  {
#pragma omp for schedule(static)
    for (i = 1; i < block_count; ++i) {
      for (j = 0; j < i; ++j) {
        toLeftSide(&this->matrix, i, block_count, block_size);
        shiftUp(&matrix2.matrix, i, block_count, block_size);
      }
    }
  }
  for (i = 0; i < block_count; ++i) {
#pragma omp parallel num_threads(num_threads) private(j, k, i, l) \
    shared(matrix2, res_matrix) {
#pragma omp for schedule(static)
    for (j = 0; j < block_count; ++j) {
      for (k = 0; k < block_count; ++k) {
        mutiplyByBlock(this->matrix, matrix2.matrix, &res_matrix, j, k,
                       block_size);
      }
    }
#pragma omp for schedule(static)
    for (l = 0; l < block_count; ++l) {
      toLeftSide(&this->matrix, l, block_count, block_size);
      shiftUp(&matrix2.matrix, l, block_count, block_size);
    }
  }
}
return res_matrix;
}
