// Copyright 2023 Binko Alexandr
#include "../../../modules/task_1/binko_a_kanon/kanon.h"

void Matrix::toLeftSide(std::vector<std::vector<double>> *matr, size_t pos,
                        size_t block_count, size_t skew) {
  std::vector<std::vector<double>> tmp_matr;

  for (size_t i = 0; i < skew; ++i) {
    std::vector<double> vec(skew);
    tmp_matr.push_back(vec);
    for (size_t j = 0; j < skew; ++j) {
      tmp_matr[i][j] = matr->at(i + skew * pos).at(j);
    }
  }
  for (size_t k = 0; k < block_count - 1; ++k) {
    for (size_t i = 0; i < skew; ++i) {
      for (size_t j = 0; j < skew; ++j) {
        matr->at(i + skew * pos).at(j + skew * k) =
            matr->at(i + skew * pos).at(j + skew * (k + 1));
      }
    }
  }
  for (size_t i = 0; i < skew; ++i) {
    for (size_t j = 0; j < skew; ++j) {
      matr->at(i + skew * pos).at(j + skew * (block_count - 1)) =
          tmp_matr[i][j];
    }
  }
}

std::vector<std::vector<double>> Matrix::multiplyByMatrix(Matrix matrix) {
  Matrix res_matrix(size);
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      for (size_t k = 0; k < size; ++k) {
        res_matrix.matrix[i][j] += this->matrix[i][k] * matrix.matrix[k][j];
      }
    }
  }
  return res_matrix.matrix;
}

void Matrix::shiftUp(std::vector<std::vector<double>> *matr, size_t pos,
                     size_t block_count, size_t skew) {
  std::vector<std::vector<double>> tmp_matr;

  for (size_t i = 0; i < skew; ++i) {
    std::vector<double> vec(skew);
    tmp_matr.push_back(vec);
    for (size_t j = 0; j < skew; ++j) {
      tmp_matr[i][j] = matr->at(i).at(j + skew * pos);
    }
  }
  for (size_t i = 0; i < block_count - 1; ++i) {
    for (size_t j = 0; j < skew; ++j) {
      for (size_t k = 0; k < skew; ++k) {
        matr->at(j + skew * i).at(k + skew * pos) =
            matr->at(j + skew * (i + 1)).at(k + skew * pos);
      }
    }
  }
  for (size_t i = 0; i < skew; ++i) {
    for (size_t j = 0; j < skew; ++j) {
      matr->at(i + skew * (block_count - 1)).at(j + skew * pos) =
          tmp_matr[i][j];
    }
  }
}

void Matrix::mutiplyByBlock(std::vector<std::vector<double>> block1,
                            std::vector<std::vector<double>> block2,
                            std::vector<std::vector<double>> *res_block,
                            size_t shift_l, size_t shift_r, size_t skew) {
  for (size_t i = 0; i < skew; i++)
    for (size_t j = 0; j < skew; j++)
      for (size_t k = 0; k < skew; k++)
        res_block->at(i + skew * shift_l).at(j + skew * shift_r) +=
            block1[i + skew * shift_l][skew * shift_r + k] *
            block2[k + skew * shift_l][j + skew * shift_r];
}

void Matrix::fillNewMatrix(double num) {
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      matrix[i][j] = i * num;
    }
  }
}

std::vector<std::vector<double>> Matrix::KanonAlg(
    Matrix matrix2, std::vector<std::vector<double>> res_matrix,
    size_t block_size, size_t block_count) {
  for (size_t i = 1; i < block_count; ++i) {
    for (size_t j = 0; j < i; ++j) {
      toLeftSide(&this->matrix, i, block_count, block_size);
      shiftUp(&matrix2.matrix, i, block_count, block_size);
    }
  }
  for (size_t i = 0; i < block_count; ++i) {
    for (size_t j = 0; j < block_count; ++j) {
      for (size_t k = 0; k < block_count; ++k) {
        mutiplyByBlock(this->matrix, matrix2.matrix, &res_matrix, j, k,
                       block_size);
      }
    }
    for (size_t l = 0; l < block_count; ++l) {
      toLeftSide(&this->matrix, l, block_count, block_size);
      shiftUp(&matrix2.matrix, l, block_count, block_size);
    }
  }
  return res_matrix;
}
