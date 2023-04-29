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
        if (was_in_while) {
          if (to_find_adjacent_segment < i * w + 1) {
            // it is not nesessary  to check does
            // card[to_find_adjacent_segment-1].L != 0 or not because at least
            // one iteration (with  to_find_adjacent_segment-1 was performed
            card[i * w + j].L_prev_right = card[to_find_adjacent_segment - 1].L;
          }
        } else {
          if (card[to_find_adjacent_segment].p_left % m <=
                  card[i * w + j].p_right % m &&
              card[to_find_adjacent_segment].L != 0 &&
              to_find_adjacent_segment < i * w) {
            card[i * w + j].L_prev_right = card[to_find_adjacent_segment].L;
          }
        }
        was_in_while = false;
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
      //if (card[i * w + j].L_prev_left == card[i * w + j].L_prev_right &&
      //    card[i * w + j].L_prev_right != 0) {
      //  omp_set_lock(&lock);
      //  std::cout << "PREV\n";
      //  std::cout << "L = " << card[i * w + j].L << "\n";
      //  std::cout << "i = " << i << " j = " << j << "\n";
      //  std::cout << "p_left = " << card[i * (m / 2 + 1) + j].p_left << "\n";
      //  std::cout << "p_right = " << card[i * (m / 2 + 1) + j].p_right << "\n";
      //  std::cout << "prev_left = " << card[i * (m / 2 + 1) + j].L_prev_left
      //            << "\n";
      //  std::cout << "prev_right = " << card[i * (m / 2 + 1) + j].L_prev_right
      //            << "\n";
      //  std::cout << "next_left = " << card[i * (m / 2 + 1) + j].L_next_left
      //            << "\n";
      //  std::cout << "next_right = " << card[i * (m / 2 + 1) + j].L_next_right
      //            << "\n";
      //  omp_unset_lock(&lock);
      //} else {
      //  if (card[i * w + j].L_next_left == card[i * w + j].L_next_right &&
      //      card[i * w + j].L_next_right != 0) {
      //    omp_set_lock(&lock);
      //    std::cout << "L = " << card[i * w + j].L << "\n";
      //    std::cout << "i = " << i << " j = " << j << "\n";
      //    std::cout << "p_left = " << card[i * (m / 2 + 1) + j].p_left << "\n";
      //    std::cout << "p_right = " << card[i * (m / 2 + 1) + j].p_right
      //              << "\n";
      //    std::cout << "prev_left = " << card[i * (m / 2 + 1) + j].L_prev_left
      //              << "\n";
      //    std::cout << "prev_right = " << card[i * (m / 2 + 1) + j].L_prev_right
      //              << "\n";
      //    std::cout << "next_left = " << card[i * (m / 2 + 1) + j].L_next_left
      //              << "\n";
      //    std::cout << "next_right = " << card[i * (m / 2 + 1) + j].L_next_right
      //              << "\n";
      //    omp_unset_lock(&lock);
      //  }
      //}
      j++;
    }
  }
}
void third_par_pass(CardR& card, int n, int m) {
  bool been_changed = false;
  omp_lock_t lock;
  omp_init_lock(&lock);
  int w = m / 2 + 1;
  do {
    been_changed = false;
    // labels - private
#pragma omp parallel for shared(been_changed, card, w)
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < w && card[i * w + j].L > 0; j++) {
        int cur_id = i * w + j;
        size_t labels[4] = {card[cur_id].L_prev_left, card[cur_id].L_prev_right,
                            card[cur_id].L_next_left,
                            card[cur_id].L_next_right};
        size_t cur_min = UINT64_MAX;
        for (int p = 0; p < 4; p++) {
          if (labels[p] != 0 && labels[p] < cur_min) {
            cur_min = labels[p];
          }
        }
        if (cur_min < card[cur_id].L) {
          card[cur_id].L = min(card[card[cur_id].L - 1].L, cur_min);
          been_changed = true;
        }
      }
    }
  } while (been_changed);
  /*std::cout << "L" << card[20].L << "\n";
  std::cout << "prev_left = " << card[20].L_prev_left << "\n";
  std::cout << "prev_right = " << card[20].L_prev_right << "\n";
  std::cout << "next_left = " << card[20].L_next_left << "\n";
  std::cout << "next_right = " << card[20].L_next_right << "\n";*/
}

//+
// TO DO: make a documentation
void forth_par_pass(CardR& card, int n, int m) {
  size_t w = m / 2 + 1;
  omp_lock_t lock;
  omp_init_lock(&lock);
#pragma omp parallel for shared(card, n, m, w)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < w; j++) {
      size_t L = card[i * w + j].L;
      if (L > 0) {
        size_t L_i = card[L - 1].L;
        /*omp_set_lock(&lock);
        std::cout << "L = " << L << "\n";
        omp_unset_lock(&lock);*/
        while (L_i != L) {
          L_i = card[L_i - 1].L;
          L = card[L - 1].L;
        }
        card[i * w + j].L = L_i;
      }
    }
  }
}

//-
// TO DO: make a documentation
void mark_assign_pass(CardR& card, vector<vector<int>>& p_marks, int n, int m) {
  size_t w = m / 2 + 1;
  // real_numbers[counter] = label of component which should be named as counter
  vector<size_t> real_numbers;
  real_numbers.resize(n * w + 1);
  size_t counter = 1;

  omp_lock_t lock;
  omp_init_lock(&lock);
  int p = 0;
  for (; p < n; p++) {
    if (card[p * w].L != 0) {
      real_numbers[card[p * w].L] = 1;
      break;
    }
  }
  if (card[p * w].L == 0) {
    return;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < w; j++) {
      if (card[i * w + j].L == 0) {
        /*std::cout << "i = " << i << " j = " << j << "\n";*/
        break;
      }
      if (real_numbers[card[i * w + j].L] != 0) {
        card[i * w + j].L = real_numbers[card[i * w + j].L];
      } else {
        // if (card[i * w + j].L != 0) {
        counter++;
        real_numbers[card[i * w + j].L] = counter;
        card[i * w + j].L = real_numbers[card[i * w + j].L];
        //}
      }
    }
  }

  // for (int i = 0; i < n; i++) {
  //  for (int j = 0; j < w; j++) {
  //    if (card[i * w + j].L != 0)
  //      if (real_numbers[counter - 1] == card[i * w + j].L) {
  //        card[i * w + j].L = counter;
  //      } else {
  //        if (real_numbers[counter - 1] == 0 && counter == 1) {
  //          real_numbers[counter - 1] = card[i * w + j].L;
  //          card[i * w + j].L = counter;
  //        } else {
  //          std::cout << "card[i*w+j].L = " << card[i * w + j].L << "\n";
  //          std::cout << "real_num[counter-1] = " << real_numbers[counter - 1]
  //                    << "\n";
  //          counter++;
  //          card[i * w + j].L = counter;
  //        }
  //      }
  //  }
  //}

  //#pragma omp parallel for shared(n, m, card, p_marks, w)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < w; j++) {
      if (card[i * w + j].L == 0) {
        break;
      }
      //&& card[i * w + j].L != 0; j++) {
      size_t begin = card[i * w + j].p_left % m;
      size_t end = card[i * w + j].p_right % m;
      while (begin <= end) {
        p_marks[i][begin] = card[i * w + j].L;
        begin++;
      }
    }
  }
}

void par_marking(vector<vector<int>>& image, const int n, const int m,
                 vector<vector<int>>& marks, const int k_unnamed) {
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
  CardR card(m, n);
  /*if (n < 20)
    for (int i = 0; i < (m / 2 + 1) * n; i++) {
      card[i].L = 0;
    }*/
  //std::cout << "m/2+1=" << m / 2 + 1 << "\n";
  first_par_pass(p_image, card, n, m, k_back);
  second_par_pass(card, n, m);

  // std::cout << "\n";
  /* for (int i = 0; i < n; i++) {
     for (int j = 0; j < m / 2 + 1; j++) {
       std::cout << card[i * (m / 2 + 1) + j].L << " ";
     }
     std::cout << "\n";
   }*/
  third_par_pass(card, n, m);
  forth_par_pass(card, n, m);
  /*for (int i = 0; i < n; i++) {
    for (int j = 0; j < m / 2 + 1; j++) {
      std::cout << card[i * (m / 2 + 1) + j].L << " ";
    }
    std::cout << "\n";
  }*/
  mark_assign_pass(card, marks, n, m);
  /*for (int i = 0; i < n; i++) {
    for (int j = 0; j < m / 2 + 1; j++) {
      std::cout << card[i * (m / 2 + 1) + j].L << " ";
    }
    std::cout << "\n";
  }*/
}

// void first_eq_pass(int** image, EqLabel* labels, const int n, const int m,
//                   const int k_back) {
//#pragma omp parallel for shared(n, m, k_back, labels, image)
//  for (int i = 0; i < n; i++) {
//    for (int j = 0; j < m; j++) {
//      if (image[i][j] != k_back) {
//        labels[i * m + j].label = i * m + j + 1;
//      }
//    }
//  }
//}
// void second_eq_pass(EqLabel* labels, const int n, const int m) {
//  size_t up_left_right_down[4];
//  for (int i = 0; i < 4; i++) {
//    up_left_right_down[i] = UINT64_MAX;
//  }
//  bool changed;
//  omp_lock_t lock;
//  omp_init_lock(&lock);
//  do {
//    changed = false;
//#pragma omp parallel for shared(n, m, labels) firstprivate(up_left_right_down)
//    for (int i = 0; i < n; i++) {
//      for (int j = 0; j < m; j++) {
//        for (int t = 0; t < 4; t++) {
//          up_left_right_down[t] = UINT64_MAX;
//        }
//        if (i > 0) {
//          up_left_right_down[0] = labels[(i - 1) * m + j].label;
//        }
//        if (i < n - 1) {
//          up_left_right_down[3] = labels[(i + 1) * m + j].label;
//        }
//        if (j > 0) {
//          up_left_right_down[1] = labels[i * m + j - 1].label;
//        }
//        if (j < m - 1) {
//          up_left_right_down[2] = labels[i * m + j + 1].label;
//        }
//        omp_set_lock(&lock);
//        size_t min_neighbour =
//            min(min(up_left_right_down[0], up_left_right_down[1]),
//                min(up_left_right_down[2], up_left_right_down[3]));
//        if (min_neighbour < labels[i * m + j].label) {
//          labels[i * m + j].label = min_neighbour;
//          changed = true;
//        }
//        omp_unset_lock(&lock);
//      }
//    }
//  } while (changed);
//}
// void third_eq_pass(EqLabel* labels, const int n, const int m, int** marks) {
//  size_t counter = 0;
//  size_t cur_label = 1;
//  for (int i = 0; i < n; i++) {
//    for (int j = 0; j < m; j++) {
//      ////////////////////////////////////////////////////////////////////////////////////if
//      ///()
//      if (labels[i * m + j].label > cur_label) {
//        cur_label++;
//        labels[i * m + j] = cur_label;
//      }
//    }
//  }
//  for (int i = 0; i < n; i++) {
//    for (int j = 0; j < m; j++) {
//      marks[i][j] = labels[i * m + j].label;
//    }
//  }
//}

// void par_marking(vector<vector<int>>& image, const int n, const int m,
//                 vector<vector<int>>& marks, const int k_unnamed = 0) {
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
//  EqLabel* labels = new EqLabel[n * m];
//  first_eq_pass(p_image, labels, n, m, k_back);
//  second_eq_pass(labels, n, m);
//  third_eq_pass(labels, n, m, p_marks);
//}

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
