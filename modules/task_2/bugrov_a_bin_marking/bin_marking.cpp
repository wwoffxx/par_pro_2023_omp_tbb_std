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

// void par_marking(const vector<vector<int>>& image, const int n, const int m,
//                 vector<vector<int>>& marks, const int k_unnamed = 0) {
//  int cur_mark = 1;
//  const int k_back = 1;  // backround of image (white color)
//  int** p_image = new int*[n];
//  omp_lock_t lock;
//  omp_init_lock(&lock);
//  int thread_num;
//  for (int i = 0; i < n; i++) {
//    p_image[i] = new int[m];
//    p_image[i] = image[i].data();
//  }
//  int** p_marks = new int*[n];
//  for (int i = 0; i < n; i++) {
//    p_marks[i] = new int[m];
//    p_marks[i] = marks[i].data();
//  }
//  if (p_image[0][0] != k_back) {
//    p_marks[0][0] = cur_mark;
//  }
//  // parent_components[i] == parent of i-th component
//  int* parent_components =
//      new int[(n * m + 1) / 2 +
//              1];  // last +1 is because 0-th component does not exist
//  for (int i = 0; i < (n * m + 1) / 2 + 1; i++) {
//    parent_components[i] = 0;
//  }
//  for (int j = 1; j < m; j++) {
//    if (p_image[0][j] != k_back) {
//      if (p_image[0][j - 1] != k_back) {
//        p_marks[0][j] = cur_mark;
//      } else {
//        p_marks[0][j] = ++cur_mark;
//      }
//    }
//  }
//  // making parent components - first pass
//  /*
//  {
//  thread_num = omp_get_thread_num();
//#pragma omp
//  */
//#pragma omp parallel for shared(p_image, p_marks) private(i, j) \
//    firstprivate(parent_components)
//  for (int i = 1; i < n; i++) {
//    for (int j = 0; j < m; j++) {
//      if (p_image[i][j] != k_back) {
//        if (j > 0 && p_image[i][j - 1] != k_back) {
//          p_marks[i][j] = cur_mark;
//        } else {
//          p_marks[i][j] = ++cur_mark;
//        }
//      }
//    }
//    for (int j = 1; j < m; j++) {
//      // if-s
//      if (p_image[i][j] != k_back) {
//        if (p_image[i - 1][j] != k_back) {
//          // north pixel is black
//          p_marks[i][j] = p_marks[i - 1][j];
//          if (p_image[i][j - 1] != k_back &&
//              p_marks[i][j - 1] != p_marks[i - 1][j]) {
//            // mark of north pixel != mark of west pixel
//            // add to equivalent union;
//            parent_components[p_marks[i][j - 1]] = p_marks[i - 1][j];
//          }
//        } else {
//          // north pixel is white
//          if (p_image[i][j - 1] != k_back) {
//            p_marks[i][j] = p_image[i][j - 1];
//          } else {
//            // also west pixel is white
//            omp_set_lock(&lock);
//            cur_mark++;
//            omp_unset_lock(&lock);
//            p_marks[i][j] = cur_mark;
//          }
//        }
//      }
//    }
//  }
//  // merging - second pass;
//  for (int i = 0; i < (n * m + 1) / 2 + 1; i++) {
//    if (parent_components[i]) {
//      if (parent_components[parent_components[i]]) {
//        parent_components[i] = parent_components[parent_components[i]];
//      }
//    }
//  }
//#pragma omp parallel for shared(p_marks) private(i, j)
//  for (int i = 0; i < n; i++) {
//    for (int j = 0; j < n; j++) {
//      if (parent_components[p_marks[i][j]]) {
//        p_marks[i][j] = parent_components[p_marks[i][j]];
//      }
//    }
//  }
//  {
//#pragma omp barrier
//  }
//  for (int i = 0; i < (n * m + 1) / 2 + 1; i++) {
//    parent_components[i] = (n * m + 1);
//  }
//  int comp_counter = 1;
//  cur_mark = 1;
//  // first pass - making real name of component
//}

// +
void first_par_pass(int** p_image, CardR& card, int n, int m,
                    const int k_back) {
#pragma omp parallel for shared(p_image, card) /*private(i, j)*/
  for (size_t i = 0; i < n; i++) {
    size_t R_n = 0;
    R tmp;
    for (size_t j = 0; j < m; j++) {
      if (p_image[i][j] != k_back) {
        R_n++;
        tmp.p_left = i * m + j;
        tmp.L_next_left = tmp.L_next_right = tmp.L_prev_left =
            tmp.L_prev_right = 0;
        tmp.L = i * (m / 2 + 1) + R_n;
        while (p_image[i][j] != k_back && j < m) {
          j++;
        }
        tmp.p_right = i * m + j - 1;
        card[i * (m / 2 + 1) + R_n - 1] = tmp;
      }
    }
  }
}

//-
// prev or next left != prev or next right
void second_par_pass(CardR& card, int n, int m) {
  omp_lock_t lock;  ///////////////////////////////////////////////////
  omp_init_lock(&lock);
  const int w = m / 2 + 1;  // width of card
  bool right_exists = false;
  std::cout << "w = " << w << "\n";
  bool was_in_while = false;
#pragma omp parallel for shared(card, n, m, w, was_in_while)
  for (int i = 0; i < n; i++) {
    int j = 0;
    // finding all segments in row
    while (j < w && card[i * w + j].L != 0) {
      int to_find_adjacent_segment = (i - 1) * w;
      // finding left neighbour in (i-1)-th row
      while (i > 0 && to_find_adjacent_segment < i * w &&
             card[to_find_adjacent_segment].L != 0 &&
             card[to_find_adjacent_segment].p_right % m <
                 card[i * w + j].p_left % m) {
        to_find_adjacent_segment++;
      }
      if (i > 0 && to_find_adjacent_segment <= i * w &&
          card[to_find_adjacent_segment].L > 0 &&
          card[to_find_adjacent_segment].p_left % m <=
              card[i * w + j].p_right % m) {
        card[i * w + j].L_prev_left = card[to_find_adjacent_segment].L;
        to_find_adjacent_segment++;

        // finding right neighbour in (i-1)-th row
        while (card[to_find_adjacent_segment].L != 0 &&
               to_find_adjacent_segment < i * w &&
               card[to_find_adjacent_segment].p_left % m <=
                   card[i * w + j].p_right % m) {
          to_find_adjacent_segment++;
          was_in_while = true;
        }
        if (card[to_find_adjacent_segment].L != 0 &&
            to_find_adjacent_segment < i * w + 1) {
          if (was_in_while) {
            if (card[to_find_adjacent_segment - 1].p_left % m <=
                card[i * w + j].p_right % m) {
              card[i * w + j].L_prev_right =
                  card[to_find_adjacent_segment - 1].L;
            }
          } else {
            if (card[to_find_adjacent_segment].p_left % m <=
                card[i * w + j].p_right % m) {
              card[i * w + j].L_prev_right = card[to_find_adjacent_segment].L;
            }
          }
          was_in_while = false;
        }
      }

      to_find_adjacent_segment = (i + 1) * w;

      // finding left neighbour in (i+1)-th row
      while (i < n - 1 && to_find_adjacent_segment < (i + 2) * w &&
             card[to_find_adjacent_segment].L != 0 &&
             card[to_find_adjacent_segment].p_right % m <
                 card[i * w + j].p_left % m) {
        to_find_adjacent_segment++;
      }
      if (i < n - 1 && to_find_adjacent_segment <= (i + 2) * w &&
          card[to_find_adjacent_segment].L != 0 &&
          card[to_find_adjacent_segment].p_left % m <=
              card[i * w + j].p_right % m) {
        card[i * w + j].L_next_left = card[to_find_adjacent_segment].L;
        to_find_adjacent_segment++;
        // finding right neighbour in (i+1)-th row
        while (card[to_find_adjacent_segment].L != 0 &&
               card[to_find_adjacent_segment].p_left % m <=
                   card[i * w + j].p_right % m) {
          to_find_adjacent_segment++;
          was_in_while = true;
        }
        if (card[to_find_adjacent_segment].L != 0 &&
            to_find_adjacent_segment < (i + 2) * w) {
          if (was_in_while) {
            if (card[to_find_adjacent_segment - 1].p_left % m <=
                card[i * w + j].p_right % m) {
              card[i * w + j].L_next_right =
                  card[to_find_adjacent_segment - 1].L;
            }
          } else {
            if (card[to_find_adjacent_segment].p_left % m <=
                card[i * w + j].p_right % m) {
              card[i * w + j].L_next_right = card[to_find_adjacent_segment].L;
            }
          }
          was_in_while = false;
        }
      }
      /*
      omp_set_lock(&lock);
       std::cout << "L = " << card[i * w + j].L << "\n";
       std::cout << "i = " << i << " j = " << j << "\n";
       std::cout << "p_left = " << card[i * (m / 2 + 1) + j].p_left << "\n";
       std::cout << "p_right = " << card[i * (m / 2 + 1) + j].p_right << "\n";
       std::cout << "prev_left = " << card[i * (m / 2 + 1) + j].L_prev_left
                 << "\n";
       std::cout << "prev_right = " << card[i * (m / 2 + 1) + j].L_prev_right
                 << "\n";
       std::cout << "next_left = " << card[i * (m / 2 + 1) + j].L_next_left
                 << "\n";
       std::cout << "next_right = " << card[i * (m / 2 + 1) + j].L_next_right
                 << "\n";
       omp_unset_lock(&lock);
       */
      if (card[i * w + j].L_prev_left == card[i * w + j].L_prev_right &&
              card[i * w + j].L_prev_right != 0 ||
          card[i * w + j].L_next_left == card[i * w + j].L_next_right &&
              card[i * w + j].L_next_right != 0) {
        omp_set_lock(&lock);
        std::cout << "L = " << card[i * w + j].L << "\n";
        std::cout << "i = " << i << " j = " << j << "\n";
        if (card[i * w + j].L_prev_left == card[i * w + j].L_prev_right)
          std::cout << "prev\n";
        else
          std::cout << "next\n";
        omp_unset_lock(&lock);
      }

      j++;
    }
  }
}
void third_par_pass(CardR& card, int n, int m) {
  bool been_changed;
  do {
    been_changed = false;
#pragma omp parallel for shared(been_changed, card) /*private(i, j, cur_id)*/
    for (int i = 0; i < n; i++) {
      int j = 0;
      while (j < (m / 2 + 1) && card[i * m / 2 + j].L > 0) {
        int cur_id = i * m / 2 + j;
        int cur_min =
            min(min(card[cur_id].L_next_left, card[cur_id].L_next_right),
                min(card[cur_id].L_prev_left, card[cur_id].L_prev_right));
        if (cur_min < card[cur_id].L) {
          card[cur_id].L = cur_min;
          been_changed = true;
        }
      }
    }
  } while (been_changed);
}

void forth_par_pass(CardR& card, int n, int m) {
#pragma omp parallel for shared(card, n, m)
  for (int i = 0; i < n; i++) {
  }
}

void mark_assign_pass(CardR& card, vector<vector<int>>& p_marks, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m / 2 + 1 && card[i * m / 2 + j].L != 0; j++) {
      size_t begin = card[i * m / 2 + j].p_left % m;
      size_t end = card[i * m / 2 + j].p_right % m;
      while (begin <= end) {
        p_marks[i][begin] = card[i * m / 2 + j].L;
        begin++;
      }
    }
  }
}

// void par_marking(vector<vector<int>>& image, const int n, const int m,
//                 vector<vector<int>>& marks, const int k_unnamed) {
//  int cur_mark = 1;
//  const int k_back = 1;  // backround of image (white color)
//  int** p_image = new int*[n];
//  omp_lock_t lock;  ///////////////////////////////////////////////////
//  omp_init_lock(&lock);
//  for (int i = 0; i < n; i++) {
//    p_image[i] = new int[m];
//    p_image[i] = image[i].data();
//  }
//  int** p_marks = new int*[n];
//  for (int i = 0; i < n; i++) {
//    p_marks[i] = new int[m];
//    p_marks[i] = marks[i].data();
//  }
//  if (p_image[0][0] != k_back) {
//    p_marks[0][0] = cur_mark;
//  }
//  // std::cout << "before creating card\n";
//  CardR card(m, n);
//  // std::cout << "before initializing\n";
//  for (int i = 0; i < (m / 2 + 1) * n; i++) {
//    card[i].L = 0;
//  }
//  std::cout << "m/2+1=" << m / 2 + 1 << "\n";
//  // std::cout << "before passes\n";
//  first_par_pass(p_image, card, n, m, k_back);
//  // std::cout << "after first pass\n";
//  for (int i = 0; i < (m / 2 + 1) * n; i++) {
//    std::cout << card[i].L << " ";
//  }
//  std::cout << "\n";
//  second_par_pass(card, n, m);
//  for (int i = 0; i < (m / 2 + 1) * n; i++) {
//    std::cout << card[i].L << " ";
//  }
//  std::cout << "\n";
//  third_par_pass(card, n, m);
//  mark_assign_pass(card, marks, n, m);
//  for (int i = 0; i < (m / 2 + 1) * n; i++) {
//    std::cout << card[i].L << " ";
//  }
//}

void first_eq_pass(int** image, EqLabel* labels, const int n, const int m,
                   const int k_back) {
#pragma omp parallel for shared(n, m, k_back, labels, image)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (image[i][j] != k_back) {
        labels[i * m + j].label = i * m + j + 1;
      }
    }
  }
}

// size_t find_min_neighbour(EqLabel* labels, const int n, const int m, int i,
//  int j) {
//   }

void second_eq_pass(EqLabel* labels, const int n, const int m) {
  size_t up_left_right_down[4];
  for (int i = 0; i < 4; i++) {
    up_left_right_down[i] = UINT64_MAX;
  }
  bool changed;
  omp_lock_t lock;
  omp_init_lock(&lock);
  do {
    changed = false;
#pragma omp parallel for shared(n, m, labels) firstprivate(up_left_right_down)
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        for (int t = 0; t < 4; t++) {
          up_left_right_down[t] = UINT64_MAX;
        }
        if (i > 0) {
          up_left_right_down[0] = labels[(i - 1) * m + j].label;
        }
        if (i < n - 1) {
          up_left_right_down[3] = labels[(i + 1) * m + j].label;
        }
        if (j > 0) {
          up_left_right_down[1] = labels[i * m + j - 1].label;
        }
        if (j < m - 1) {
          up_left_right_down[2] = labels[i * m + j + 1].label;
        }
        omp_set_lock(&lock);
        size_t min_neighbour =
            min(min(up_left_right_down[0], up_left_right_down[1]),
                min(up_left_right_down[2], up_left_right_down[3]));
        if (min_neighbour < labels[i * m + j].label) {
          labels[i * m + j].label = min_neighbour;
          changed = true;
        }
        omp_unset_lock(&lock);
      }
    }
  } while (changed);
}
void third_eq_pass(EqLabel* labels, const int n, const int m, int** marks) {
  size_t counter = 0;
  size_t cur_label = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ////////////////////////////////////////////////////////////////////////////////////if ()
      if (labels[i * m + j].label > cur_label) {
        cur_label++;
        labels[i * m + j] = cur_label;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      marks[i][j] = labels[i * m + j].label;
    }
  }
}

void par_marking(vector<vector<int>>& image, const int n, const int m,
                 vector<vector<int>>& marks, const int k_unnamed = 0) {
  int cur_mark = 1;
  const int k_back = 1;  // backround of image (white color)
  int** p_image = new int*[n];
  omp_lock_t lock;  ///////////////////////////////////////////////////
  omp_init_lock(&lock);
  for (int i = 0; i < n; i++) {
    p_image[i] = new int[m];
    p_image[i] = image[i].data();
  }
  int** p_marks = new int*[n];
  for (int i = 0; i < n; i++) {
    p_marks[i] = new int[m];
    p_marks[i] = marks[i].data();
  }
  if (p_image[0][0] != k_back) {
    p_marks[0][0] = cur_mark;
  }
  EqLabel* labels = new EqLabel[n * m];
  first_eq_pass(p_image, labels, n, m, k_back);
  second_eq_pass(labels, n, m);
  third_eq_pass(labels, n, m, marks);
}

// void par_marking(vector<vector<int>>& image, const int n, const int m,
//                 vector<vector<int>>& marks, const int k_unnamed = 0) {
//  int cur_mark = 0;
//  const int k_back = 1;
//  queue<pair<int, int>> cur_queue;
//    omp_lock_t lock;  ///////////////////////////////////////////////////
//  omp_init_lock(&lock);
//#pragma omp parallel for shared(image, marks,k_back,cur_mark)
//  for (int i = 0; i < n; i++) {
//    for (int j = 0; j < m; j++) {
//      if (image[i][j] != k_back && (marks)[i][j] == k_unnamed) {
//        cur_mark += 1;
//        (marks)[i][j] = cur_mark;
//        omp_set_lock(&lock);
//        cur_queue.push(pair<int, int>(i, j));
//        omp_unset_lock(&lock);
//        while (!cur_queue.empty()) {
//          omp_set_lock(&lock);
//          pair<int, int> tmp = cur_queue.front();
//          cur_queue.pop();
//          omp_unset_lock(&lock);
//          if (tmp.first - 1 >= 0) {
//            if ((marks)[tmp.first - 1][tmp.second] == k_unnamed &&
//                image[tmp.first - 1][tmp.second] != k_back) {
//              (marks)[tmp.first - 1][tmp.second] = cur_mark;
//              omp_set_lock(&lock);
//              cur_queue.push(pair<int, int>(tmp.first - 1, tmp.second));
//              omp_unset_lock(&lock);
//            }
//          }
//          if (tmp.second - 1 >= 0) {
//            if ((marks)[tmp.first][tmp.second - 1] == k_unnamed &&
//                image[tmp.first][tmp.second - 1] != k_back) {
//              (marks)[tmp.first][tmp.second - 1] = cur_mark;
//              omp_set_lock(&lock);
//              cur_queue.push(pair<int, int>(tmp.first, tmp.second - 1));
//              omp_unset_lock(&lock);
//            }
//          }
//          if (tmp.first + 1 < n) {
//            if ((marks)[tmp.first + 1][tmp.second] == k_unnamed &&
//                image[tmp.first + 1][tmp.second] != k_back) {
//              (marks)[tmp.first + 1][tmp.second] = cur_mark;
//              omp_set_lock(&lock);
//              cur_queue.push(pair<int, int>(tmp.first + 1, tmp.second));
//              omp_unset_lock(&lock);
//            }
//          }
//          if (tmp.second + 1 < m) {
//            if ((marks)[tmp.first][tmp.second + 1] == k_unnamed &&
//                image[tmp.first][tmp.second + 1] != k_back) {
//              (marks)[tmp.first][tmp.second + 1] = cur_mark;
//              omp_set_lock(&lock);
//              cur_queue.push(pair<int, int>(tmp.first, tmp.second + 1));
//              omp_unset_lock(&lock);
//            }
//          }
//        }
//      }
//    }
//  }
//}
