// Copyright 2023 Popov Nikita
#include "../../../modules/task_3/popov_n_alg_of_jarvis_tbb/alg_of_jarvis_tbb.h"

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

struct Functor {
  int cu;
  int ne;
  const std::vector<Point>& points;
  Functor(const std::vector<Point>& input, int ne, int cu)
      : ne(ne), cu(cu), points(input) {}
  Functor(const Functor& second, tbb::split)
      : ne(second.ne), cu(second.cu), points(second.points) {}
  void operator()(const tbb::blocked_range<int>& r) {
    for (int i = r.begin(); i != r.end(); ++i) {
      if (check_orientation(points[cu], points[ne], points[i]) ==
          point_or::counterclockwsise) {
        ne = i;
      }
    }
  }
  void join(const Functor& second) {
    if (check_orientation(points[cu], points[ne], points[second.ne]) ==
            point_or::counterclockwsise ||
        check_orientation(points[cu], points[ne], points[second.ne]) ==
                point_or::colliniar &&
            sqrtdist(points[cu], points[ne]) <
                sqrtdist(points[cu], points[second.ne])) {
      ne = second.ne;
    }
  }
};

std::vector<Point> get_convex_body_tbb(const std::vector<Point>& points) {
  int size = points.size();
  if (size < 3)
    return std::vector<Point>();
  else if (size == 3)
    return std::vector<Point>(points);

  std::set<Point> body;
  int st = 0;
  for (int i = 1; i < size; i++) {
    if (points[i] < points[st]) {
      st = i;
    }
  }
  int cu = st;
  int ne;
  while (true) {
    ne = (cu + 1) % size;
    Functor temp(points, ne, cu);
    tbb::parallel_reduce(tbb::blocked_range<int>(0, size), temp);
    ne = temp.ne;
    for (int i = 0; i < size; i++) {
      if (check_orientation(points[cu], points[ne], points[i]) ==
          point_or::colliniar) {
        body.insert(points[i]);
      }
    }
    cu = ne;
    if (ne == st) {
      break;
    }
  }
  return std::vector<Point>(body.begin(), body.end());
}

std::vector<Point> get_convex_body(const std::vector<Point>& points) {
  int size = points.size();
  if (size < 3)
    return std::vector<Point>();
  else if (size == 3)
    return std::vector<Point>(points);

  std::set<Point> body;

  int st = 0;
  for (int i = 1; i < size; i++) {
    if (points[i] < points[st]) {
      st = i;
    }
  }

  int to_push = st;
  int ne;
  while (true) {
    ne = (to_push + 1) % size;
    for (int i = 0; i < size; i++) {
      if (check_orientation(points[to_push], points[ne], points[i]) ==
              point_or::counterclockwsise ||
          check_orientation(points[to_push], points[ne], points[i]) ==
                  point_or::colliniar &&
              sqrtdist(points[to_push], points[ne]) <
                  sqrtdist(points[to_push], points[i])) {
        ne = i;
      }
    }
    for (int i = 0; i < size; i++) {
      if (check_orientation(points[to_push], points[ne], points[i]) ==
          point_or::colliniar) {
        body.insert(points[i]);
      }
    }
    to_push = ne;
    if (st == ne) {
      break;
    }
  }

  return std::vector<Point>(body.begin(), body.end());
}
