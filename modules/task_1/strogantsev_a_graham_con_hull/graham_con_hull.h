// Copyright 2023 Strogantsev Anton
#ifndef MODULES_TASK_1_STROGANTSEV_A_GRAHAM_CON_HULL_GRAHAM_CON_HULL_H_
#define MODULES_TASK_1_STROGANTSEV_A_GRAHAM_CON_HULL_GRAHAM_CON_HULL_H_

#include <vector>

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

enum class Orientation {
    COLLINEAR,
    LEFT,
    RIGHT,
};

Orientation getOrientation(const Point& p1, const Point& p2, const Point& anchor);

bool comparePointsOnAnchor(const Point& p1, const Point& p2, const Point& anchor);

std::vector<Point> constructConvexHull(const std::vector<Point>& points);

#endif  // MODULES_TASK_1_STROGANTSEV_A_GRAHAM_CON_HULL_GRAHAM_CON_HULL_H_
