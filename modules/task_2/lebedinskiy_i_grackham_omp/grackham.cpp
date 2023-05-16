// Copyright 2023 Lebedinskiy Ilya
#include "../../../modules/task_2/lebedinskiy_i_grackham_omp/grackham.h"
std::pair<double, double> p0;

double distance(const std::pair<double, double>& dot1,
    const std::pair<double, double>& dot2) {
    return (dot1.first - dot2.first) * (dot1.first - dot2.first) +
        (dot1.second - dot2.second) * (dot1.second - dot2.second);
}

int rotation(const std::pair<double, double>& dot1,
    const std::pair<double, double>& dot2,
    const std::pair<double, double>& dot3) {
    double val = (dot2.second - dot1.second) * (dot3.first - dot2.first) -
        (dot2.first - dot1.first) * (dot3.second - dot2.second);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

int compare(const void* vp1, const void* vp2) {
    std::pair<double, double>* p1 = (std::pair<double, double>*)vp1;
    std::pair<double, double>* p2 = (std::pair<double, double>*)vp2;

    int o = rotation(p0, *p1, *p2);
    if (o == 0)
        return (distance(p0, *p2) >= distance(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

std::vector<std::pair<double, double>> grackham_seq(
    std::vector<std::pair<double, double>>::iterator beg,
    std::vector<std::pair<double, double>>::iterator end) {
    std::vector<std::pair<double, double>> vec(end - beg);
    std::copy(beg, end, vec.begin());
    if (vec.size() == 0) {
        std::vector<std::pair<double, double>> zero = { { 0, 0 } };
        return zero;
    }
    if (vec.size() == 3) {
        return vec;
    }
    int min = 0;
    double ymin = vec[0].second;
    int size = vec.size();
    for (int i = 1; i < size; i++) {
        double y = vec[i].second;

        if ((y < ymin) || (ymin == y && vec[i].first < vec[min].first)) {
            ymin = vec[i].second;
            min = i;
        }
    }
    std::swap(vec[0], vec[min]);
    p0 = vec[0];
    qsort(&vec[1], size - 1, sizeof(std::pair<double, double>), compare);
    std::vector<std::pair<double, double>> res;
    res.push_back(vec[0]);
    res.push_back(vec[1]);
    res.push_back(vec[2]);

    for (int i = 3; i < size; i++) {
        while (res.size() > 1 &&
            rotation(res[res.size() - 2], res.back(), vec[i]) != 2) {
            res.pop_back();
        }
        res.push_back(vec[i]);
    }
    return res;
}

std::vector<std::pair<double, double>> gen_dots(int vectorSize) {
    std::mt19937 gen;
    std::vector<std::pair<double, double>> vec(vectorSize);
    double lower_bound = 0;
    double upper_bound = 10000;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;
    for (int i = 0; i < vectorSize; i++) {
        vec[i] = std::make_pair(unif(re), unif(re));
    }
    return vec;
}

std::vector<std::pair<double, double>> grackham_omp(
    std::vector<std::pair<double, double>>::iterator beg,
    std::vector<std::pair<double, double>>::iterator end,
    std::size_t n_threads) {
    if (n_threads == 0) {
        throw "incorrect number of threads";
    }

    int step = (end - beg) / n_threads;
    std::vector<std::pair<double, double>> last_points;

#pragma omp parallel num_threads(n_threads)
    {
        std::size_t t_number = omp_get_thread_num();
        std::vector<std::pair<double, double>> local_scan;

        if (t_number == n_threads - 1) {
            local_scan = grackham_seq(beg + step * t_number, end);
        } else {
            local_scan = grackham_seq(beg + step * t_number, beg + step * (t_number + 1));
        }
#pragma omp critical
        {
            for (std::size_t i = 0; i < local_scan.size(); ++i) {
                last_points.push_back(local_scan[i]);
            }
        }
    }
    return grackham_seq(last_points.begin(), last_points.end());
}
