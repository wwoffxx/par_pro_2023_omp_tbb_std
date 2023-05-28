// Copyright 2023 me
#ifndef MODULES_TASK_3_KROLEVETS_N_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_
#define MODULES_TASK_3_KROLEVETS_N_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include "tbb/tbb.h"

enum class point_orientation { colliniar, clockwise, counterclockwsise };

struct Point {
  int x = 0;
  int y = 0;

  Point() = default;
  Point(int x, int y) : x(x), y(y) {}
  bool operator>(const Point& other) const {
    return std::make_pair(x, y) > std::make_pair(other.x, other.y);
  }
  bool operator<(const Point& other) const {
    return std::make_pair(x, y) < std::make_pair(other.x, other.y);
  }
  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Point& other) const { return !(*this == other); }
};
point_orientation orientation(const Point&, const Point&, const Point&);
std::vector<Point> get_convex_hull(const std::vector<Point>&);
std::vector<Point> get_convex_hull_tbb(const std::vector<Point>&);
double dist2(const Point&, const Point&);

#endif  // MODULES_TASK_3_KROLEVETS_N_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_"
