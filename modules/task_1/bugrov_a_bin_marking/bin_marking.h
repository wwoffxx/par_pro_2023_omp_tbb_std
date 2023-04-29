// Copyright 2023 Bugrov Andrey
#pragma once
#include <time.h>  // rand seed

#include <map>     // pairs
#include <queue>   // queue for Depth-first search
#include <random>  // mt19937
#include <vector>  // vector
using std::mt19937;
using std::pair;
using std::queue;
using std::vector;

// void seq_marking(const vector<vector<int>>& image, const int N,
//                vector<vector<int>>& marks, const int k_unnamed);
void marking(int** image, const int n, const int m, int** marks,
             const int k_unnamed);
void marking(const vector<vector<int>>& image, const int n, const int m,
             vector<vector<int>>* marks, const int k_unnamed);
// void par_marking(const vector<vector<int>>& image, const int n, const int m,
//             vector<vector<int>>* marks, const int k_unnamed);

bool are_matrix_eq(const vector<vector<int>>& a, const vector<vector<int>>& b,
                   int n, int m);
