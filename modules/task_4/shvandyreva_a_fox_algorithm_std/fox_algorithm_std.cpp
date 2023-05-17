// Copyright 2023 Shvandyreva Alina
#include <chrono>
#include <thread>
#include <mutex>
#include "../../../modules/task_4/shvandyreva_a_fox_algorithm_std/fox_algorithm_std.h"

static matrix sum_block(const matrix& A, const matrix& B) {
    matrix result(A.size(), std::vector<double>(A[0].size()));
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

static matrix multiply_block(const matrix& A, const matrix& B) {
    matrix result(A.size(), std::vector<double>(B[0].size()));
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            result[i][j] = 0;
            for (int k = 0; k < A[0].size(); k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

matrix generate_matrix(size_t x_size, size_t y_size) {
    matrix result(y_size, std::vector<double>(x_size));
    std::random_device device;
    std::mt19937 mt(device());
    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            result[y][x] = 0.1 * (mt() % 100);
        }
    }
    return result;
}

matrix generate_identity_matrix(size_t size) {
    matrix result(size, std::vector<double>(size));
    for (int i = 0; i < size; i++) {
        result[i][i] = 1;
    }
    return result;
}

matrix seq_multiply(const matrix& A, const matrix& B) {
    return multiply_block(A, B);
}

matrix std_multiply(const matrix& A, const matrix& B, int tasks_by_dim) {
    const int td = tasks_by_dim < 1 ? 1 : tasks_by_dim;
    if (td == 1) {
        return multiply_block(A, B);
    }
    matrix result(A.size(), std::vector<double>(B[0].size()));

    const int p = A.size() / td; // portion
    const int real_workers_count = std::thread::hardware_concurrency();
    std::vector<std::thread> workers;
    std::mutex lock;
    std::mutex iter_lock;
    std::vector<std::pair<int, int>> a(td * td);
    std::vector<std::pair<int, int>> b(td * td);
    for (size_t ind = 0; ind != td * td; ind++) {
        int x = ind % td;
        int y = ind / td;

        a[ind].first = y + x;
        a[ind].second = y;

        b[ind].first = x;
        b[ind].second = y + x;

        if (a[ind].first >= td) {
            a[ind].first -= td;
        }
        if (b[ind].second >= td) {
            b[ind].second -= td;
        }
    }
    int task_counter = td * td;
    int iter_counter = td - 1;
    int free_workers = 0;
    for (size_t w = 0; w < real_workers_count; w++) {
        workers.emplace_back([&]() {
            while (true)
            {
                lock.lock();
                free_workers++;
                if (task_counter == 0) {
                    if (free_workers == real_workers_count && iter_counter != 0) {
                        iter_counter--;
                        task_counter = td * td;
                    }
                    else {
                        while (task_counter == 0) {
                            if (iter_counter == 0) {
                                lock.unlock();
                                return;
                            }
                            lock.unlock();
                            using namespace std::chrono_literals;
                            std::this_thread::sleep_for(1ms);
                            lock.lock();
                        }
                    }
                }
                int ind = --task_counter;
                free_workers--;
                lock.unlock();

                int& a_x = a[ind].first;
                int& a_y = a[ind].second;
                int& b_x = b[ind].first;
                int& b_y = b[ind].second;
                int& x = b_x;
                int& y = a_y;
                for (int i = 0; i < p; i++) {
                    for (int j = 0; j < p; j++) {
                        for (int k = 0; k < p; k++) {
                            result[i + y * p][j + x * p]
                                += A[i + a_y * p][k + a_x * p] * B[k + b_y * p][j + b_x * p];
                        }
                    }
                }

                if (++a_x >= td) {
                    a_x = 0;
                }
                if (++b_y >= td) {
                    b_y = 0;
                }
            }
            });
    }
    for (size_t w = 0; w < real_workers_count; w++) {
        workers[w].join();
    }

    return result;
}
