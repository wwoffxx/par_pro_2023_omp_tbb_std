// Copyright 2023 Popov Nikita

#ifndef MODULES_TASK_2_POPOV_N_ALG_OF_JARVIS_OMP_ALG_OF_JARVIS_OMP_H_
#define MODULES_TASK_2_POPOV_N_ALG_OF_JARVIS_OMP_ALG_OF_JARVIS_OMP_H_

#include <omp.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <utility>
#include <vector>

enum class point_or { colliniar, clockwise, counterclockwsise };

struct Point {
  int x = 0;
  int y = 0;

  Point() = default;
  Point(int x, int y) : x(x), y(y) {}
  bool operator>(const Point& two) const {
    return std::make_pair(x, y) > std::make_pair(two.x, two.y);
  }
  bool operator<(const Point& two) const {
    return std::make_pair(x, y) < std::make_pair(two.x, two.y);
  }
  bool operator==(const Point& two) const { return x == two.x && y == two.y; }
  bool operator!=(const Point& two) const { return !(*this == two); }
};
point_or check_orientation(const Point&, const Point&, const Point&);
std::vector<Point> get_convex_body(const std::vector<Point>&);
std::vector<Point> get_convex_body_omp(const std::vector<Point>&);
double sqrtdist(const Point&, const Point&);

#endif  // MODULES_TASK_2_POPOV_N_ALG_OF_JARVIS_OMP_ALG_OF_JARVIS_OMP_H_"
