// Copyright 2023 Okulov Stepan
#include "../../../modules/task_3/okulov_s_marking_comp/marking_comp.h"

#include <tbb/blocked_range2d.h>
#include <tbb/parallel_for.h>
//#include <tbb/tbb.h>

#include <algorithm>
#include <map>
#include <vector>

void change(std::map<int, int>* mp, int first, int second) {
  if ((*mp).count(first)) {
    if (second < (*mp)[first]) {
      change(mp, (*mp)[first], second);
    } else if (second > (*mp)[first]) {
      change(mp, second, (*mp)[first]);
    }
  } else {
    (*mp)[first] = second;
  }
}

void marking(std::vector<std::vector<int>>* img) {
  int label = 0;
  std::map<int, int> eq;
  int C;  // up
  int B;  // left
  for (int i = 0; i < (*img).size(); i++) {
    for (int j = 0; j < (*img)[0].size(); j++) {
      if ((*img)[i][j] == 0) continue;
      if (j == 0)
        B = 0;
      else
        B = (*img)[i][j - 1];
      if (i == 0)
        C = 0;
      else
        C = (*img)[i - 1][j];
      if ((B == 0 && C != 0) || (C == 0 && B != 0)) {
        (*img)[i][j] = std::max(B, C);
      } else if (B == 0 && C == 0) {
        label++;
        (*img)[i][j] = label;
      } else if (B != 0 && C != 0) {
        if (B == C) {
          (*img)[i][j] = C;
        } else {
          (*img)[i][j] = std::min(B, C);
          change(&eq, std::max(B, C),std::min(B, C));
        }
      }
    }
  }

  for (auto x = eq.begin(); x != eq.end(); x++) {
    if (!eq.count(x->second)) continue;
    int k = x->second;
    while (eq.count(k)) k = eq[k];
    eq[x->first] = k;
  }

  tbb::parallel_for(
      tbb::blocked_range2d<int>(0, (*img).size(), 0, (*img)[0].size()),
      [&](const tbb::blocked_range2d<int>& r) {
        for (int i = r.rows().begin(); i != r.rows().end(); ++i) {
          for (int j = r.cols().begin(); j != r.cols().end(); ++j) {
            if ((*img)[i][j] == 0) continue;

            if (eq.count((*img)[i][j])) (*img)[i][j] = eq[(*img)[i][j]];
          }
        }
      });
}
