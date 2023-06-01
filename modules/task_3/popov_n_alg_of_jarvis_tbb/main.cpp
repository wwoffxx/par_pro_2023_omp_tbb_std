// Copyright 2023 Popov Nikita
#include <gtest/gtest.h>

#include "../../../modules/task_3/popov_n_alg_of_jarvis_tbb/alg_of_jarvis_tbb.h"

void create_vec(std::vector<Point>* vect, uint32_t size) {
  std::set<Point> unique_point;
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<int> dist(0, size << 1);
  while (unique_point.size() != size) {
    unique_point.insert(Point(dist(rng), dist(rng)));
  }
  std::copy(unique_point.begin(), unique_point.end(),
            std::back_inserter(*vect));
  std::shuffle(vect->begin(), vect->end(), rng);
}

TEST(convex_body_test, on_return_empty_vector) {
  std::vector<Point> input;
  auto output = get_convex_body(input);
  auto output2 = get_convex_body_tbb(input);
  EXPECT_EQ(output.size(), 0);
  EXPECT_EQ(output2.size(), 0);
}

TEST(convex_body_test, on_body_of_three) {
  std::vector<Point> input;
  create_vec(&input, 3);
  auto output = get_convex_body(input);
  auto output2 = get_convex_body_tbb(input);
  bool thing1 = output.size() == output2.size();
  bool thing2 = output == output2;
  bool thing3 = output.size() == 3;
  EXPECT_EQ(thing1, true);
  EXPECT_EQ(thing2, true);
  EXPECT_EQ(thing3, true);
}

TEST(convex_body_test, on_body_of_ten) {
  std::vector<Point> input;
  create_vec(&input, 10);
  auto output = get_convex_body(input);
  auto output2 = get_convex_body_tbb(input);
  bool thing1 = output.size() == output2.size();
  bool thing2 = output == output2;
  EXPECT_EQ(thing1, true);
  EXPECT_EQ(thing2, true);
}

TEST(convex_body_test, body_of_hundred) {
  std::vector<Point> input;
  create_vec(&input, 100);
  auto output = get_convex_body(input);
  auto output2 = get_convex_body_tbb(input);
  bool thing1 = output.size() == output2.size();
  bool thing2 = output == output2;
  EXPECT_EQ(thing1, true);
  EXPECT_EQ(thing2, true);
}

TEST(convex_body_test, body_of_thousand) {
  std::vector<Point> input;
  create_vec(&input, 500);
  auto output = get_convex_body(input);
  auto output2 = get_convex_body_tbb(input);
  bool thing1 = output.size() == output2.size();
  bool thing2 = output == output2;
  EXPECT_EQ(thing1, true);
  EXPECT_EQ(thing2, true);
}
