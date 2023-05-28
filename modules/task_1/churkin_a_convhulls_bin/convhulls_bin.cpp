// Copyright 2023 Churkin Aleksandr
#include <vector>
#include <utility>
#include <random>
#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
#include "../../../modules/task_1/churkin_a_convhulls_bin/convhulls_bin.h"

// 1. Generates random binary image with height M and width N
std::vector<int> GetRandomBinImage(int M, int N) {
    std::default_random_engine rnd{std::random_device { } ()};
    std::uniform_int_distribution<> dist(0, 1);

    std::vector<int> image(M * N);

    for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++) image[i * N + j] = dist(rnd);

    return image;
}

void PrintImage(const std::vector<int>& image, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) std::cout << image[i * N + j] << " ";
        std::cout << '\n';
    }
}

void BFS(std::vector<int>* image, int M, int N, int yStart, int xStart,
         int label) {
    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(xStart, yStart));
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if (x >= 0 && y >= 0 && y < M && x < N && image->at(y * N + x) == 1) {
            (*image)[y * N + x] = label;

            q.push(std::make_pair(x - 1, y - 1));  // bottom left
            q.push(std::make_pair(x - 1, y));      // left
            q.push(std::make_pair(x - 1, y + 1));  // top left
            q.push(std::make_pair(x, y + 1));      // top
            q.push(std::make_pair(x + 1, y + 1));  // top right
            q.push(std::make_pair(x + 1, y));      // right
            q.push(std::make_pair(x, y - 1));      // bottom
            q.push(std::make_pair(x + 1, y - 1));  // bottom right
        }
    }
}

// 2. Marks components on image (labeling starts from 2)
void MarkComponents(std::vector<int>* image, int M, int N) {
    int label = 2;
    // i is y coordinate
    for (int i = 0; i < M; i++)
        // j is x coordinate
        for (int j = 0; j < N; j++) {
            if (image->at(i * N + j) == 1)
                BFS(image, M, N, i, j, label), label++;
        }
}

double rotate(std::pair<int, int> p1, std::pair<int, int> p2,
              std::pair<int, int> p3) {
    return (p2.first - p1.first) * (p3.second - p2.second) -
           (p2.second - p1.second) * (p3.first - p2.first);
}

std::vector<std::pair<int, int>> GrahamScan(
    std::vector<std::pair<int, int>> points) {
    if (points.size() <= 2) return points;

    std::vector<std::pair<int, int>> result;

    // Finding minimal point - point with minimum x and y (left bottom point)
    std::pair<int, int> minPoint = points[0];
    int minPointIdx = 0;

    for (size_t i = 1; i < points.size(); i++) {
        if (points[i].first < minPoint.first ||
            (points[i].first == minPoint.first &&
             points[i].second < minPoint.second)) {
            minPoint = points[i];
            minPointIdx = i;
        }
    }

    // Removing minimal point from our points
    std::swap(points[minPointIdx], points[points.size() - 1]);
    points.pop_back();

    // Sorting points by our custom criteria
    std::sort(points.begin(), points.end(),
              [minPoint](const std::pair<int, int>& p1,
                         const std::pair<int, int>& p2) {
                  // Vector v1 coordinates
                  double v1x = p1.first - minPoint.first;
                  double v1y = p1.second - minPoint.second;
                  // Vector v2 coordinates
                  double v2x = p2.first - minPoint.first;
                  double v2y = p2.second - minPoint.second;

                  // Performing comparison by det
                  double det = v1x * v2y - v1y * v2x;

                  if (det > 0) {
                      // v1 < v2 by det
                      return true;
                  } else if (det == 0) {
                      // v1 == v2 by det. Let's compare by length of vectors
                      double len_v1 = sqrt(pow(v1x, 2) + pow(v1y, 2));
                      double len_v2 = sqrt(pow(v2x, 2) + pow(v2y, 2));

                      return len_v1 < len_v2;
                  } else {
                      // v1 > v2 by det
                      return false;
                  }
              });

    // Then we do Graham scan
    // minPoint and points[0]
    // are the first points of our convex hull
    result.push_back(minPoint), result.push_back(points[0]);

    for (size_t i = 1; i < points.size(); i++) {
        // p1
        std::pair<int, int> p1 = result[result.size() - 2];
        // p2
        std::pair<int, int> p2 = result[result.size() - 1];
        // p3
        std::pair<int, int> p3 = points[i];

        double rot = rotate(p1, p2, p3);
        // p1, p2, p3 on one line -> replacing p2 with p3
        if (rot == 0) {
            result[result.size() - 1] = p3;
        } else if (rot < 0) {
            // While p1, p2, p3 form right turn -> exclude p2
            while (rotate(result[result.size() - 2], result[result.size() - 1],
                          p3) <= 0)
                result.pop_back();
            result.push_back(p3);
        } else {
            // left turns are ok - just adding p3 to our result
            result.push_back(p3);
        }
    }

    return result;
}

// 3. Leaves only convex hulls on image
std::map<int, std::vector<std::pair<int, int>>> LeaveOnlyHulls(
    std::vector<int>* image, int M, int N) {
    std::map<int, std::vector<std::pair<int, int>>> components;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            int pixVal = (*image)[i * N + j];

            if (pixVal > 0)
                // pixVal - 1 fills up to resolve an issue of numbering from 2
                // in components we have keys (components) from 1 to number of
                // components
                components[pixVal - 1].push_back(std::make_pair(j, i));
        }

    // Then, we should launch Graham for every component to get its convex hull
    std::map<int, std::vector<std::pair<int, int>>> hulls;

    for (auto& kv : components) {
        int label = kv.first;
        auto& component = kv.second;

        // if (label == 2) // TODO DELETE THIS COND
        hulls[label] = GrahamScan(component);
    }

    for (int i = 0; i < M * N; i++) (*image)[i] = 0;

    for (auto& kv : hulls) {
        int label = kv.first;
        auto& hullpoints = kv.second;

        for (std::pair<int, int> p : hullpoints)
            (*image)[p.second * N + p.first] = label;
    }

    return hulls;
}
