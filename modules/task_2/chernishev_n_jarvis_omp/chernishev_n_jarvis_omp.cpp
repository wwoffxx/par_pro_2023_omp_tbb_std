// Copyright 2023 Chernishev Nikita

#include "../../../modules/task_2/chernishev_n_jarvis_omp/chernishev_n_jarvis_omp.h"

#include <omp.h>

std::vector<dot> JarvisSeq(std::vector<dot> Dots) {
    std::vector<dot> res;

    dot first = *Dots.begin();
    for (auto dot : Dots) {
        if (first.y > dot.y) first = dot;
        if ((first.y == dot.y) && (first.x > dot.x)) first = dot;
    }
    res.push_back(first);

    auto second = Dots.begin();
    for (auto dot = Dots.begin(); dot != Dots.end(); ++dot) {
        if (getRotate(first, *dot) > getRotate(first, *second)) second = dot;
        if (getRotate(first, *dot) == getRotate(first, *second)) {
            if (getLen(first, *second) > getLen(first, *dot)) second = dot;
        }
    }
    res.push_back(*second);
    Dots.erase(second);

    while (true) {
        int ResSize = res.size();
        dot lastRes = res.at(ResSize - 1);
        dot prevLastRes = res.at(ResSize - 2);

        auto next = Dots.begin();
        for (auto i = Dots.begin(); i != Dots.end(); i++) {
            if (getCos(prevLastRes, lastRes, *next) >
                getCos(prevLastRes, lastRes, *i))
                next = i;
        }
        if (*next == first) {
            return res;
        } else {
            res.push_back(*next);
            Dots.erase(next);
        }
    }
}

std::vector<dot> JarvisOMP(std::vector<dot> Dots, int threadsNom) {
    std::vector<dot> res;
    omp_set_num_threads(threadsNom);
#pragma omp parallel
    {
        int threadNom = omp_get_thread_num();
        int localSize;
        int delta = Dots.size() / threadsNom;
        int ost = Dots.size() % threadsNom;
        std::vector<dot> localVector;

        if (threadNom == 0) {
            localSize = ost + delta;
            localVector =
                std::vector<dot>(Dots.begin(), Dots.begin() + localSize);
        } else {
            localSize = Dots.size() / threadsNom;
            localVector = std::vector<dot>(
                Dots.begin() + (localSize * threadNom) + ost,
                Dots.begin() + (localSize * (threadNom + 1)) + ost);
        }
        std::vector<dot> localRes = JarvisSeq(localVector);
#pragma omp critical
        { res.insert(res.end(), localRes.begin(), localRes.end()); }
    }
    return JarvisSeq(res);
}

bool isEqual(const std::vector<dot>& lhs, const std::vector<dot>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (int i = 0; i < rhs.size(); i++) {
        if (rhs.at(i) != lhs.at(i)) return false;
    }
    return true;
    
}
