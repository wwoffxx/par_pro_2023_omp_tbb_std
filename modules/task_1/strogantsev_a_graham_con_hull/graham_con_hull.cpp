// Copyright 2023 Strogantsev Anton
#include <algorithm>
#include "../../../modules/task_1/strogantsev_a_graham_con_hull/graham_con_hull.h"


Orientation getOrientation(const Point& p1, const Point& p2, const Point& anchor) {
    int value = (p2.y - p1.y) * (anchor.x - p2.x) - (p2.x - p1.x) * (anchor.y - p2.y);
    if (value == 0) return Orientation::COLLINEAR;
    if (value > 0) return Orientation::LEFT;
    return Orientation::RIGHT;
}

bool comparePointsOnAnchor(const Point& p1, const Point& p2, const Point& anchor) {
    auto orientation = getOrientation(anchor, p1, p2);
    if (orientation == Orientation::COLLINEAR)
        return ((p1.x - anchor.x) * (p1.x - anchor.x) + (p1.y - anchor.y) * (p1.y - anchor.y))
            < ((p2.x - anchor.x) * (p2.x - anchor.x) + (p2.y - anchor.y) * (p2.y - anchor.y));
    return orientation == Orientation::RIGHT;
}

std::vector<Point> constructConvexHull(const std::vector<Point>& points) {
    if (points.size() < 3) return points;

    Point anchor = *std::min_element(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        if (p1.y == p2.y) return p1.x < p2.x;
        return p1.y < p2.y;
    });

    auto pointsCopy = points;
    std::sort(pointsCopy.begin(), pointsCopy.end(), [&](const Point& p1, const Point& p2) {
        return comparePointsOnAnchor(p1, p2, anchor);
    });

    std::vector<Point> stack;
    stack.push_back(pointsCopy[0]);
    stack.push_back(pointsCopy[1]);
    stack.push_back(pointsCopy[2]);

    for (int i = 3; i < pointsCopy.size(); i++) {
        while (stack.size() > 1 &&
            getOrientation(stack[stack.size() - 2], stack.back(), pointsCopy[i]) != Orientation::RIGHT)
            stack.pop_back();
        stack.push_back(pointsCopy[i]);
    }
    return stack;
}
