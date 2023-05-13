// Copyright 2023 Kosterin Alexey
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

#include "../../../modules/task_3/kosterin_a_jarvis_tbb/jarvis.h"

int Cross(SVector a, SVector b) { return a.x * b.y - b.x * a.y; }

std::vector<SPoint> CreateArray(int size) {
  if (size < 3) {
    throw size;
  }
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<SPoint> arr(size);
  for (int i = 0; i < size; i++) {
    arr[i].x = gen() % 10;
    arr[i].y = gen() % 10;
  }
  return arr;
}

void Swap(SPoint &arr1, SPoint &arr2) {
  SPoint buf;
  buf.x = arr1.x;
  buf.y = arr1.y;

  arr1.x = arr2.x;
  arr1.y = arr2.y;

  arr2.x = buf.x;
  arr2.y = buf.y;
}
bool ChekJarvis(std::vector<SPoint> jarArr) {
  int size = jarArr.size();
  for (int i = 0; i < size; i++) {
    int fPoint = i, sPoint = i + 1, thPoint = i + 2;
    if (sPoint >= size) {
      sPoint = 0;
      thPoint = 1;
    }
    if (thPoint >= size) {
      thPoint = 0;
    }
    if (Cross(SVector(jarArr[fPoint], jarArr[sPoint]),
              SVector(jarArr[sPoint], jarArr[thPoint])) < 0)
      return false;
  }
  return true;
}

std::vector<SPoint> DoJarvisSeq(std::vector<SPoint> arr, int size) {
  for (int i = 1; i < size; i++) {
    if (arr[i].y < arr[0].y)
      Swap(arr[0], arr[i]);
    else if (arr[i].y == arr[0].y && arr[i].x < arr[0].x)
      Swap(arr[0], arr[i]);
  }
  std::vector<SPoint> point;
  int currP = 0;
  bool fl = true;
  while (true) {
    point.push_back(arr[currP]);
    int id = 0;
    for (int i = 0; i < arr.size(); i++) {
      if (i != currP && (fl == true || Cross(SVector(arr[currP], arr[i]),
                                           SVector(arr[currP], arr[id])) > 0)) {
        id = i;
        fl = false;
      }
    }
    if (id == 0) {
      break;
    } else {
      currP = id;
    }
  }
  return point;
}

int Direction(const SPoint& cur, const SPoint& next, const SPoint& tmp) {
  return (tmp.x - cur.x) * (next.y - cur.y) -
         (tmp.y - cur.y) * (next.x - cur.x);
}

bool checkDistance(const SPoint& cur, const SPoint& next, const SPoint& tmp) {
  int distNextCur = (next.x - cur.x) * (next.x - cur.x) +
                    (next.y - cur.y) * (next.y - cur.y);
  int distTmpCur = (tmp.x - cur.x) * (tmp.x - cur.x) +
                   (tmp.y - cur.y) * (tmp.y - cur.y);
  if (distNextCur < distTmpCur) {
    return true;
  }
  return false;
}

std::vector<SPoint> tbbJarvis(const std::vector<SPoint>& points) {
  int numberOfPoints = static_cast<int>(points.size());
  if (numberOfPoints == 0) {
    throw -1;
  }
  if (numberOfPoints < 2) {
    return points;
  }
  SPoint start = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(1, numberOfPoints), points[0],
      [&points](tbb::blocked_range<size_t>& r, SPoint localStart) -> SPoint {
        auto begin = r.begin(), end = r.end();
        for (auto i = begin; i != end; i++) {
          if ((points[i].y < localStart.y) || (points[i].y == localStart.y && points[i].x < localStart.x)) {
            localStart = points[i];
          }
        }
        return localStart;
      },
      [](const SPoint& localStart, const SPoint& start) -> SPoint {
        return ((localStart.y < start.y) ||(localStart.y == start.y && localStart.x < start.x)) ? localStart : start;
      });
  std::vector<SPoint> result;
  result.push_back(start);
  SPoint currentPoint = start;
  SPoint nextPoint;
  do {
    if (currentPoint.y == points[0].y && currentPoint.x == points[0].x) {
      nextPoint = points[1];
    } else {
      nextPoint = points[0];
    }
    currentPoint = tbb::parallel_reduce(
        tbb::blocked_range<size_t>(0, numberOfPoints), nextPoint,
        [&currentPoint, &points](tbb::blocked_range<size_t>& r,
                                 SPoint localNext) -> SPoint {
          auto begin = r.begin(), end = r.end();
          for (auto i = begin; i != end; i++) {
            int direction = Direction(currentPoint, localNext, points[i]);
            if (direction > 0) {
              localNext = points[i];
            } else if (direction == 0) {
              if (checkDistance(currentPoint, localNext, points[i])) {
                localNext = points[i];
              }
            }
          }
          return localNext;
        },
        [&currentPoint](const SPoint& nextPoint,
                        const SPoint& localNext) -> SPoint {
          int direction = Direction(currentPoint, nextPoint, localNext);
          if (direction > 0) {
            return localNext;
          } else if (direction == 0) {
            if (checkDistance(currentPoint, nextPoint, localNext)) {
              return localNext;
            }
          }
          return nextPoint;
        });
    nextPoint = currentPoint;
    result.push_back(nextPoint);
  } while (currentPoint.x != start.x && currentPoint.y != start.y);
  result.pop_back();
  return result;
}
