// Copyright 2023 me
#include "../../../modules/task_4/krolevets_n_jarvis_algorithm/jarvis_algorithm.h"

point_orientation orientation(const Point& p, const Point& q, const Point& r) {
  int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  if (val == 0) return point_orientation::colliniar;
  return (val > 0) ? point_orientation::clockwise
                   : point_orientation::counterclockwsise;
}

double dist2(const Point& a, const Point& b) {
  int dx = b.x - a.x;
  int dy = b.y - a.y;
  return dx * dx + dy * dy;
}

void thread_func(int begin, int end, int current,
                 const std::vector<Point>& points, int* per_thread_next) {
  for (int i = begin; i < end; ++i) {
    if (orientation(points[current], points[*per_thread_next], points[i]) ==
        point_orientation::counterclockwsise) {
      *per_thread_next = i;
    }
  }
}

std::vector<Point> get_convex_hull_std(const std::vector<Point>& points,
                                       int thread_num) {
  int n = points.size();
  if (n < 3)
    return std::vector<Point>();
  else if (n == 3)
    return std::vector<Point>(points);

  std::set<Point> hull;
  std::vector<int> per_thread_next(thread_num, -1);
  int start = 0;
  for (int i = 1; i < n; i++) {
    if (points[i] < points[start]) {
      start = i;
    }
  }
  int current = start;
  int next;
  while (true) {
    std::vector<std::thread> threads;
    next = (current + 1) % n;
    std::fill(per_thread_next.begin(), per_thread_next.end(), next);
    for (uint64_t i = 0; i < thread_num; ++i) {
      int operations_per_thread = (n + thread_num - 1) / thread_num;
      threads.push_back(
          std::thread(thread_func, operations_per_thread * i,
                      std::min(operations_per_thread * (i + 1), uint64_t(n)),
                      current, std::ref(points), &per_thread_next[i]));
    }
    for (uint64_t i = 0; i < thread_num; ++i) {
      threads[i].join();
    }
    for (uint64_t i = 0; i < thread_num; ++i) {
      if (orientation(points[current], points[next],
                      points[per_thread_next[i]]) ==
              point_orientation::counterclockwsise ||
          orientation(points[current], points[next],
                      points[per_thread_next[i]]) ==
                  point_orientation::colliniar &&
              dist2(points[current], points[next]) <
                  dist2(points[current], points[per_thread_next[i]])) {
        next = per_thread_next[i];
      }
    }

    for (int i = 0; i < n; i++) {
      if (orientation(points[current], points[next], points[i]) ==
          point_orientation::colliniar) {
        hull.insert(points[i]);
      }
    }
    current = next;
    if (next == start) {
      break;
    }
  }
  return std::vector<Point>(hull.begin(), hull.end());
}

std::vector<Point> get_convex_hull(const std::vector<Point>& points) {
  int n = points.size();
  if (n < 3)
    return std::vector<Point>();
  else if (n == 3)
    return std::vector<Point>(points);

  std::set<Point> hull;

  int start = 0;
  for (int i = 1; i < n; i++) {
    if (points[i] < points[start]) {
      start = i;
    }
  }

  int to_push = start;
  int next;
  while (true) {
    next = (to_push + 1) % n;
    for (int i = 0; i < n; i++) {
      if (orientation(points[to_push], points[next], points[i]) ==
              point_orientation::counterclockwsise ||
          orientation(points[to_push], points[next], points[i]) ==
                  point_orientation::colliniar &&
              dist2(points[to_push], points[next]) <
                  dist2(points[to_push], points[i])) {
        next = i;
      }
    }
    for (int i = 0; i < n; i++) {
      if (orientation(points[to_push], points[next], points[i]) ==
          point_orientation::colliniar) {
        hull.insert(points[i]);
      }
    }
    to_push = next;
    if (start == next) {
      break;
    }
  }

  return std::vector<Point>(hull.begin(), hull.end());
}
