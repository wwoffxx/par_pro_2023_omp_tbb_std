// Copyright 2023 Popov Andrey
#include <vector>
#include <string>
#include <utility>
#include <random>
#include <cmath>
#include <iostream>
#include "../../../modules/task_4/popov_fox_std/popov_fox_std.h"
#include "../../../3rdparty/unapproved/unapproved.h"

std::vector<int> getrandvect(int size) {
    std::random_device device;
    std::mt19937 generic(device());
    std::vector<int> vector(size);
    for (int  k = 0; k < size; k++) {
      vector[k] = generic() % 100;
    }
    return vector;
}

std::mutex mute;

void atOp(std::vector<int> vc, const std::string& op, std::promise<int> &&pr) {
    const int  size = vc.size();
    int reduce_el = 0;
    if (op == "+") {
        for (int  k = 0; k < size; k++) {
            std::lock_guard<std::mutex> my_lock(mute);
          reduce_el += vc[k];
        }
    } else if (op == "-") {
        for (int  k = 0; k < size; k++) {
            std::lock_guard<std::mutex> my_lock(mute);
          reduce_el -= vc[k];
        }
    }
    pr.set_value(reduce_el);
}



int getappropOps(std::vector<int> vector, const std::string &op) {
    const int numthreads = std::thread::hardware_concurrency();
    const int difference = (vector.end() - vector.begin()) / numthreads;

    std::promise<int> *proms = new std::promise<int>[numthreads];
    std::future<int> *futures = new std::future<int>[numthreads];
    std::thread *threadsstd = new std::thread[numthreads];

    int reduce_elem = 0;
    for (int k = 0; k < numthreads; k++) {
        futures[k] = proms[k].get_future();
        std::vector<int> tmp_vec(vector.begin() + k * difference,
                                 vector.begin() + (k + 1) * difference);
     threadsstd[k] = std::thread(atOp, tmp_vec, op, std::move(proms[k]));
        threadsstd[k].join();
        reduce_elem += futures[k].get();
    }

    delete []proms;
    delete []futures;
    delete []threadsstd;
    return reduce_elem;
}

int getserialOps(std::vector<int> vector, const std::string &operate) {
    const int  size = vector.size();
    int reduce_el = 0;
    if (operate == "+") {
        for (int  j = 0; j < size; j++) {
          reduce_el += vector[j];
        }
    } else if (operate == "-") {
        for (int  j = 0; j < size; j++) {
          reduce_el -= vector[j];
        }
    }
    return reduce_el;
}
