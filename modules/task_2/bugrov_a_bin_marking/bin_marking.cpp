// Copyright 2023 Bugrov Andrey
#include "../../../modules/task_2/bugrov_a_bin_marking/bin_marking.h"

// matrixes can be both vectors and arrays

// matrixes can be both vectors and arrays
void seq_marking(const vector<vector<int>>& image, const int n, const int m,
                 vector<vector<int>>* marks, const int k_unnamed = 0) {
  int cur_mark = 0;
  const int k_back = 1;
  queue<pair<int, int>> cur_queue;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (image[i][j] != k_back && (*marks)[i][j] == k_unnamed) {
        cur_mark += 1;
        (*marks)[i][j] = cur_mark;
        cur_queue.push(pair<int, int>(i, j));
        while (!cur_queue.empty()) {
          pair<int, int> tmp = cur_queue.front();
          cur_queue.pop();
          if (tmp.first - 1 >= 0) {
            if ((*marks)[tmp.first - 1][tmp.second] == k_unnamed &&
                image[tmp.first - 1][tmp.second] != k_back) {
              (*marks)[tmp.first - 1][tmp.second] = cur_mark;
              cur_queue.push(pair<int, int>(tmp.first - 1, tmp.second));
            }
          }
          if (tmp.second - 1 >= 0) {
            if ((*marks)[tmp.first][tmp.second - 1] == k_unnamed &&
                image[tmp.first][tmp.second - 1] != k_back) {
              (*marks)[tmp.first][tmp.second - 1] = cur_mark;
              cur_queue.push(pair<int, int>(tmp.first, tmp.second - 1));
            }
          }
          if (tmp.first + 1 < n) {
            if ((*marks)[tmp.first + 1][tmp.second] == k_unnamed &&
                image[tmp.first + 1][tmp.second] != k_back) {
              (*marks)[tmp.first + 1][tmp.second] = cur_mark;
              cur_queue.push(pair<int, int>(tmp.first + 1, tmp.second));
            }
          }
          if (tmp.second + 1 < m) {
            if ((*marks)[tmp.first][tmp.second + 1] == k_unnamed &&
                image[tmp.first][tmp.second + 1] != k_back) {
              (*marks)[tmp.first][tmp.second + 1] = cur_mark;
              cur_queue.push(pair<int, int>(tmp.first, tmp.second + 1));
            }
          }
        }
      }
    }
  }
}

void par_marking(const vector<vector<int>>& image, const int n, const int m,
                 vector<vector<int>>* marks, const int k_unnamed = 0) {
  int** p_image = new int*[n];
  for (int i = 0; i < n; i++) {
    p_image[i] = new int[m];
    p_image[i] = image[i].data();
  }
  // for (int i = 0; i < n; i++) {
  //  for (int j = 0; j < n; j++) {
  //    p_image[i][j] = image[i][j];
  //  }
  int** p_marks = new int*[n];
  for (int i = 0; i < n; i++) {
    p_marks[i] = new int[m];
    p_marks[i] = marks[i].data();
  }
  // for (int i = 0; i < n; i++) {
  //  for (int j = 0; j < n; j++) {
  //    p_image[i][j] = image[i][j];
  //  }
// begin of parallel section
#pragma omp_parallel
#pragma omp for shedule(static) \
    shared(n, m, p_image, p_marks, k_unnamed) private(i, j) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (p_image[i][j] == 1) {
        if (i != 0) {
          if (p_marks[i - 1][j] != k_unnamed) {
            p_marks[i][j] = p_marks[i - 1][j];
          }
        }
        if (j != 0) {
          if (p_marks[i][j - 1] != k_unnamed) {
            if (i != 0 && p_marks[i - 1][j] != p_marks[i][j - 1]) {
              // write new class of equivalency
            } else {
              p_marks[i][j] = p_marks[i][j - 1];
            }
          }
        }
      }
    }
  }
}

// end of parallel section
// merging;
}