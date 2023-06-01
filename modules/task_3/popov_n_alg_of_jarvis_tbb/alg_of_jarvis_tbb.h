// Copyright 2023 Popov Nikita
#ifndef MODULES_TASK_3_POPOV_N_ALG_OF_JARVIS_TBB_ALG_OF_JARVIS_TBB_H_
#define MODULES_TASK_3_POPOV_N_ALG_OF_JARVIS_TBB_ALG_OF_JARVIS_TBB_H_

#include <algorithm>
#include <atomic>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include "tbb/tbb.h"

enum class point_or { colliniar, clockwise, counterclockwsise };

struct Point {
  int x = 0;
  int y = 0;

  Point() = default;
  Point(int x, int y) : x(x), y(y) {}
  bool operator>(const Point& second) const {
    return std::make_pair(x, y) > std::make_pair(second.x, second.y);
  }
  bool operator<(const Point& second) const {
    return std::make_pair(x, y) < std::make_pair(second.x, second.y);
  }
  bool operator==(const Point& second) const {
    return y == second.y && x == second.x;
  }
  bool operator!=(const Point& second) const { return !(*this == second); }
};
point_or check_orientation(const Point&, const Point&, const Point&);
std::vector<Point> get_convex_body(const std::vector<Point>&);
std::vector<Point> get_convex_body_tbb(const std::vector<Point>&);
double sqrtdist(const Point&, const Point&);

#endif  // MODULES_TASK_3_POPOV_N_ALG_OF_JARVIS_TBB_ALG_OF_JARVIS_TBB_H_"
