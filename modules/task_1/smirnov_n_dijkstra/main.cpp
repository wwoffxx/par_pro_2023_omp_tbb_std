// Copyright 2023 Smirnov Nick
#include <gtest/gtest.h>

#include <vector>

#include "./dijkstra.h"

TEST(Sequential, create) {
  std::vector<std::vector<int>> a(1, std::vector<int>(1, 0));
  std::vector<int> d = dijkstra(0, a);
  ASSERT_EQ(d[0], 0);
}

TEST(Sequential, simple_path_1v) {
  std::vector<std::vector<int>> a(2, std::vector<int>(2, 0));
  a[1][0] = 1;
  a[0][1] = 1;
  std::vector<int> d = dijkstra(0, a);
  ASSERT_EQ(d[1], 1);
}

TEST(Sequential, simple_path_20v) {
  int size = 20;
  std::vector<std::vector<int>> a(size, std::vector<int>(size, 0));
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) a[i][j] = 100;
  for (int i = 0; i < size; i++) {
    if (i != size - 1) a[i][i + 1] = 1;
    a[i][i] = 0;
  }
  std::vector<int> d = dijkstra(0, a);
  ASSERT_EQ(d[size - 1], size - 1);
}

TEST(Sequential, tree) {
  int size = 20;
  std::vector<std::vector<int>> a(size, std::vector<int>(size, 0));
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) a[i][j] = ((i == j) ? 0 : 100);

  for (int i = 1; i < size; i++) {
    a[0][i] = 1;
  }
  std::vector<int> d = dijkstra(0, a);
  ASSERT_EQ(d[2], 1);
}

TEST(Sequential, tree_simp) {
  std::vector<std::vector<int>> a = {
      {0, 100, 2},
      {3, 0, 100},
      {100, 4, 0},
  };
  std::vector<int> d = dijkstra(0, a);
  ASSERT_EQ(d[1], 6);
}


