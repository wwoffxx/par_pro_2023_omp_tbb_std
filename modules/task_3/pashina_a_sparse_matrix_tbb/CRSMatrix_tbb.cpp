// Copyright 2023 Pashina Alina
#include "../../../modules/task_3/pashina_a_sparse_matrix_tbb/CRSMatrix_tbb.h"

#include <tbb/tbb.h>

#include <functional>
#include <numeric>
#include <random>
#include <string>
#include <vector>

CRSMatrix::CRSMatrix(int numC, int numR, const std::vector<double>& myVal,
                     const std::vector<int>& myColu,
                     const std::vector<int>& myPointer)
    : valueCRS(myVal),
      numCol(numC),
      colsCRS(myColu),
      numRow(numR),
      pointerCRS(myPointer) {}

CRSMatrix::CRSMatrix(int numC, int numR) {
  numCol = numC;
  numRow = numR;
}

CRSMatrix::CRSMatrix(std::vector<std::vector<double>> matr) {
  int indexCounter = 0;
  numRow = matr.size();
  numCol = matr[0].size();
  pointerCRS.push_back(indexCounter);
  for (int r = 0; r < numRow; r++) {
    for (int c = 0; c < numCol; c++) {
      if (matr[r][c] != 0) {
        valueCRS.push_back(matr[r][c]);
        indexCounter++;
        colsCRS.push_back(c);
      }
    }
    pointerCRS.push_back(indexCounter);
  }
}

bool CRSMatrix::operator==(const CRSMatrix& matr) const {
  if ((valueCRS == matr.valueCRS) && (numCol == matr.numCol) &&
      (colsCRS == matr.colsCRS) && (numRow == matr.numRow) &&
      (pointerCRS == matr.pointerCRS)) {
    return true;
  }
  return false;
}

CRSMatrix CRSMatrix::MatrixTransp() {
  CRSMatrix matr;
  std::vector<std::vector<int>> locCVec(numCol);
  std::vector<std::vector<double>> locVecVal(numCol);
  matr.numCol = numRow;
  int elemCounter = 0;
  matr.numRow = numCol;

  for (int r = 0; r < numRow; r++) {
    for (int ind = pointerCRS[r]; ind < pointerCRS[r + 1]; ind++) {
      int colInd = colsCRS[ind];
      locCVec[colInd].push_back(r);
      locVecVal[colInd].push_back(valueCRS[ind]);
    }
  }
  matr.pointerCRS.push_back(elemCounter);
  for (int col = 0; col < numCol; col++) {
    for (size_t ktmp = 0; ktmp < locCVec[col].size(); ktmp++) {
      matr.colsCRS.push_back(locCVec[col][ktmp]);
      matr.valueCRS.push_back(locVecVal[col][ktmp]);
    }
    elemCounter += locCVec[col].size();
    matr.pointerCRS.push_back(elemCounter);
  }
  return matr;
}

CRSMatrix CRSMatrix::MatrixMultTBB(CRSMatrix matr) {
  if (numCol != matr.numCol) {
    throw std::runtime_error("Wrong matrix sizes!Change rows \n");
  }
  std::vector<int> finCol, finPoint;
  std::vector<double> finVal;
  int resRows = numRow;
  std::vector<std::vector<int>> locCol(numRow);
  std::vector<std::vector<double>> locVal(numRow);
  int resCols = matr.numCol;

  int size_part = 10;
  tbb::parallel_for(
      tbb::blocked_range<int>(0, numRow, size_part),
      [&](tbb::blocked_range<int> r) {
        for (int ro1 = r.begin(); ro1 != r.end(); ++ro1) {
          for (int ro2 = 0; ro2 < matr.numRow; ro2++) {
            int first_CurPoint = pointerCRS[ro1];
            int second_CurPoint = matr.pointerCRS[ro2];
            int first_EndPoint = pointerCRS[ro1 + 1] - 1;
            int second_EndPoint = matr.pointerCRS[ro2 + 1] - 1;
            double elSum = 0;
            while ((second_CurPoint <= second_EndPoint) &&
                   (first_CurPoint <= first_EndPoint)) {
              if (colsCRS[first_CurPoint] <= matr.colsCRS[second_CurPoint]) {
                if (colsCRS[first_CurPoint] == matr.colsCRS[second_CurPoint]) {
                  elSum = elSum + valueCRS[first_CurPoint] *
                                      matr.valueCRS[second_CurPoint];
                  second_CurPoint++;
                  first_CurPoint++;
                } else {
                  first_CurPoint++;
                }
              } else {
                second_CurPoint++;
              }
            }
            if (elSum != 0) {
              locVal[ro1].push_back(elSum);
              locCol[ro1].push_back(ro2);
            }
          }
        }
      });
  int elemCounter = 0;
  finPoint.push_back(elemCounter);
  for (int indRow = 0; indRow < numRow; indRow++) {
    elemCounter = elemCounter + locCol[indRow].size();
    finCol.insert(finCol.end(), locCol[indRow].begin(), locCol[indRow].end());
    finVal.insert(finVal.end(), locVal[indRow].begin(), locVal[indRow].end());
    finPoint.push_back(elemCounter);
  }
  CRSMatrix resultMatr(resCols, resRows, finVal, finCol, finPoint);
  return resultMatr;
}

std::vector<std::vector<double>> fillZero(int cols, int rows) {
  std::vector<std::vector<double>> res(rows);
  for (int m = 0; m < rows; m++) {
    for (int n = 0; n < cols; n++) {
      res[m].push_back(0);
    }
  }
  return res;
}
std::vector<std::vector<double>> createRandomMatrix(int cols, int rows,
                                                    double perc) {
  if (perc < 0 || perc > 1) {
    throw std::runtime_error("Wrong density \n");
  }
  std::random_device mydev;
  std::vector<std::vector<double>> res = fillZero(cols, rows);
  std::mt19937 gen(mydev());
  std::uniform_real_distribution<double> genP{0.0, 1.0};
  std::uniform_real_distribution<double> genVal{0.0, 25.0};
  for (int ro = 0; ro < rows; ro++) {
    for (int col = 0; col < cols; col++) {
      if (genP(gen) <= perc) {
        res[ro][col] = genVal(gen);
      }
    }
  }
  return res;
}

std::vector<std::vector<double>> multiplyVecMatrix(
    std::vector<std::vector<double>> myFirstMatrix,
    std::vector<std::vector<double>> mySecondMatrix) {
  int colsNum = mySecondMatrix[0].size();
  int rowsNumb = myFirstMatrix.size();
  std::vector<std::vector<double>> myResCRS = fillZero(colsNum, rowsNumb);
  for (int rr = 0; rr < rowsNumb; rr++) {
    for (int cc = 0; cc < colsNum; cc++) {
      myResCRS[rr][cc] = 0;
      for (size_t k = 0; k < myFirstMatrix[0].size(); k++) {
        myResCRS[rr][cc] += myFirstMatrix[rr][k] * mySecondMatrix[k][cc];
      }
    }
  }
  return myResCRS;
}
