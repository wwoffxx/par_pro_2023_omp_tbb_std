// Copyright 2023 Popov Nikita
#include "../../../modules/task_2/popov_n_alg_of_jarvis_omp/alg_of_jarvis_omp.h"

point_or check_orientation(const Point& i, const Point& j, const Point& k) {
  int value = (j.y - i.y) * (k.x - j.x) - (j.x - i.x) * (k.y - j.y);
  if (value == 0) return point_or::colliniar;
  return (value > 0) ? point_or::clockwise : point_or::counterclockwsise;
}

double sqrtdist(const Point& one, const Point& two) {
  int sqx = two.x - one.x;
  int sqy = two.y - one.y;

  return sqx * sqx + sqy * sqy;
}

std::vector<Point> get_convex_body_omp(const std::vector<Point>& p_arr) {
  int size = p_arr.size();
  if (size < 3)
    return std::vector<Point>();
  else if (n == 3)
    return std::vector<Point>(p_arr);

  std::set<Point> body;

  int st = 0;
  for (int i = 1; i < size; i++) {
    if (p_arr[i] < p_arr[st]) {
      st = i;
    }
  }
  int cu = st;
  int ne;
  std::vector<int> to_push_by_each_thread;
#pragma omp parallel shared(st, ne, cu, size)
  {
    while (true) {
#pragma omp single
      { ne = (cu + 1) % size; }
      int private_next = ne;
      bool is_used = false;
#pragma omp for
      for (int i = 0; i < size; ++i) {
        if (check_orientation(p_arr[cu], p_arr[private_next], p_arr[i]) ==
            point_or::counterclockwsise) {
          private_next = i;
          is_used = true;
        }
      }
#pragma omp critical
      {
        if (is_used) {
          to_push_by_each_thread.push_back(private_next);
        }
      }
#pragma omp barrier
#pragma omp single
      {
        for (int i = 0; i < to_push_by_each_thread.size(); ++i) {
          if (check_orientation(p_arr[cu], p_arr[ne],
                                p_arr[to_push_by_each_thread[i]]) ==
                  point_or::counterclockwsise ||
              check_orientation(p_arr[cu], p_arr[ne],
                                p_arr[to_push_by_each_thread[i]]) ==
                      point_or::colliniar &&
                  sqrtdist(p_arr[cu], p_arr[ne]) <
                      sqrtdist(p_arr[cu], p_arr[to_push_by_each_thread[i]])) {
            ne = to_push_by_each_thread[i];
          }
        }
        to_push_by_each_thread.clear();
        for (int i = 0; i < n; i++) {
          if (check_orientation(p_arr[cu], p_arr[ne], p_arr[i]) ==
              point_or::colliniar) {
            body.insert(p_arr[i]);
          }
        }
        cu = ne;
      }
      if (ne == st) {
        break;
      }
#pragma omp barrier
    }
  }
  return std::vector<Point>(body.begin(), body.end());
}

std::vector<Point> get_convex_body(const std::vector<Point>& p_arr) {
  int size = p_arr.size();
  if (size < 3)
    return std::vector<Point>();
  else if (size == 3)
    return std::vector<Point>(p_arr);

  std::set<Point> body;

  int st = 0;
  for (int i = 1; i < size; i++) {
    if (p_arr[i] < p_arr[st]) {
      st = i;
    }
  }

  int to_push = st;
  int ne;
  while (true) {
    ne = (to_push + 1) % size;
    for (int i = 0; i < size; i++) {
      if (check_orientation(p_arr[to_push], p_arr[ne], p_arr[i]) ==
              point_or::counterclockwsise ||
          check_orientation(p_arr[to_push], p_arr[ne], p_arr[i]) ==
                  point_or::colliniar &&
              sqrtdist(p_arr[to_push], p_arr[ne]) <
                  sqrtdist(p_arr[to_push], p_arr[i])) {
        ne = i;
      }
    }
    for (int i = 0; i < size; i++) {
      if (check_orientation(p_arr[to_push], p_arr[ne], p_arr[i]) ==
          point_or::colliniar) {
        body.insert(p_arr[i]);
      }
    }
    to_push = ne;
    if (st == ne) {
      break;
    }
  }

  return std::vector<Point>(body.begin(), body.end());
}
