// Copyright 2023 Strogantsev Anton
#include <gtest/gtest.h>
#include "./graham_con_hull.h"

TEST(ConvexHull, EmptyVector) {
    std::vector<Point> points;
    auto hull = constructConvexHull(points);
    EXPECT_TRUE(hull.empty());
}

TEST(ConvexHull, TwoPoints) {
    std::vector<Point> points{ {0, 0}, {1, 1} };
    auto hull = constructConvexHull(points);
    EXPECT_EQ(hull.size(), 2);
    EXPECT_EQ(hull[0], Point(0, 0));
    EXPECT_EQ(hull[1], Point(1, 1));
}

TEST(ConvexHull, ThreePoints) {
    std::vector<Point> points{ {0, 0}, {1, 1}, {0, 1} };
    auto hull = constructConvexHull(points);
    EXPECT_EQ(hull.size(), 3);
    EXPECT_EQ(hull[0], Point(0, 0));
    EXPECT_EQ(hull[1], Point(1, 1));
    EXPECT_EQ(hull[2], Point(0, 1));
}

TEST(ConvexHull, FourPoints) {
    std::vector<Point> points{ {0, 0}, {1, 1}, {0, 1}, {1, 0} };
    auto hull = constructConvexHull(points);
    EXPECT_EQ(hull.size(), 4);
    EXPECT_EQ(hull[0], Point(0, 0));
    EXPECT_EQ(hull[1], Point(1, 0));
    EXPECT_EQ(hull[2], Point(1, 1));
    EXPECT_EQ(hull[3], Point(0, 1));
}

TEST(ConvexHull, PointsInALine) {
    std::vector<Point> points{ {0, 0}, {1, 0}, {2, 0}, {3, 0} };
    auto hull = constructConvexHull(points);
    EXPECT_EQ(hull.size(), 2);
    EXPECT_EQ(hull[0], Point(0, 0));
    EXPECT_EQ(hull[1], Point(3, 0));
}
