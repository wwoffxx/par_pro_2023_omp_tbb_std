// Copyright 2023 me
#ifndef MODULES_TASK_1_KROLEVETS_N_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_
#define MODULES_TASK_1_KROLEVETS_N_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

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
int orientation(Point p, Point q, Point r);
std::vector<Point> get_convex_hull(const std::vector<Point>& points);

#endif  // MODULES_TASK_1_KROLEVETS_N_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_
