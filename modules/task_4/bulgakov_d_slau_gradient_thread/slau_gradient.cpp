// Copyright 2023 Bulgakov Daniil

#include "../../../modules/task_4/bulgakov_d_slau_gradient_thread/slau_gradient.h"

#define NOMINMAX

// #define DEBUG

#ifdef DEBUG
    #include <omp.h>
#endif

//----------------------------- Test Data Generation --------------------------

dmat generateMatrix(int size, unsigned int seed) {
    dmat res = dmat(size, std::vector<double>(size));
    dvec v = generateVector(size, seed);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            res[i][j] = v[i] * v[j];
        }
        res[i][i] += size;
    }
    return res;
}
dvec generateVector(int size, unsigned int seed) {
    dvec res = dvec(size);
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> urd(-5, 5);
    for (int i = 0; i < size; i++) {
        res[i] = urd(mt);
    }
    return res;
}

//----------------------------- Sequential Computing Methods ------------------

double vec_vec(const dvec &a, const dvec &b) {
    return std::inner_product(a.begin(), a.end(), b.begin(), 0.0);
}

dvec matrix_vec(const dmat &a, const dvec &b) {
    dvec res(a.size());
    for (int i = 0; i < a.size(); i++) {
        res[i] =  vec_vec(a[i], b);
    }
    return res;
}

dvec vec_vec_comb(double ma, const dvec& a, double mb, const dvec& b) {
    dvec res(a.size());
    for (int i = 0; i < a.size(); i++) {
        res[i] = ma * a[i] + mb * b[i];
    }
    return res;
}

double vec_norm(const dvec& a) {
    return sqrt(vec_vec(a, a));
}

//----------------------------- Parallel Computing Methods --------------------

void part_matrix_vec(const dmat &a, const dvec &b, double * result,
                    int start, int end) {
    for (int i = start; i < end; i++) {
        result[i] = vec_vec(a[i], b);
    }
}

dvec std_matrix_vec(const dmat &a, const dvec &b) {
    dvec res(a.size());
    const int nthreads = std::thread::hardware_concurrency();
    const int delta = b.size() / nthreads;
    std::vector<std::thread> threads;

    for (int i = 0; i < nthreads; i++) {
        int end = (i + 1) * delta;
        if (end > b.size()) end = b.size();
        if (i == nthreads - 1) end = b.size();
        threads.emplace_back(part_matrix_vec, std::cref(a), std::cref(b),
                              res.data(), i * delta, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return res;
}

void part_vec_vec(const dvec &a, const dvec &b, int start, int end,
                        std::promise<double> && pr) {
    pr.set_value(std::inner_product(a.begin() + start,
                                    a.begin() + end,
                                    b.begin() + start,
                                    0.0));
}

double std_vec_vec(const dvec &a, const dvec &b) {
    double reduction_res = 0.0;

    const int nthreads = std::thread::hardware_concurrency();
    const int delta = b.size() / nthreads;
    std::vector<std::thread>  threads(nthreads);
    std::vector<std::promise<double>> promises(nthreads);
    std::vector<std::future<double>>  futures(nthreads);

    for (int i = 0; i < nthreads; i++) {
        futures[i] = promises[i].get_future();
        int end = (i + 1) * delta;
        if (end > b.size()) end = b.size();
        if (i == nthreads - 1) end = b.size();
        threads[i] = std::thread(part_vec_vec, std::cref(a), std::cref(b),
                              i * delta, end, std::move(promises[i]));
        threads[i].join();
        reduction_res += futures[i].get();
    }
    // std::cout << "Res = " << reduction_res;

    return reduction_res;
}

void std_vec_vec_comb(double ma, const dvec& a,
                        double mb, const dvec& b, std::promise<dvec> && pr) {
    dvec res(a.size());
    for (int i = 0; i < a.size(); i++) {
        res[i] = ma * a[i] + mb * b[i];
    }
    pr.set_value(res);
}

//----------------------------- Conjugate Method Algorithm --------------------


dvec solve(const dmat &a, const dvec& b) {
    dvec res(a.size(), 0.0);

    dvec r(b);
    dvec p(r);

    #ifdef DEBUG
    double begin = omp_get_wtime();
    #endif

    for (int i = 0; i < a.size(); i++) {
        dvec r_prev;
        dvec mv = matrix_vec(a, p);
        r_prev = r;

        double d = vec_vec(r, r) / std::max(vec_vec(p, mv), SMOL);
        res = vec_vec_comb(1.0, res, d, p);
        r = vec_vec_comb(1.0, r, -d, mv);

        if (vec_norm(r) < SMOL) break;

        double s = vec_vec(r, r) / std::max(vec_vec(r_prev, r_prev), SMOL);
        p = vec_vec_comb(1.0, r, s, p);
    }

    #ifdef DEBUG
    double end = omp_get_wtime();
    std::cout << "SEQ TIME " << (end - begin) << std::endl;
    #endif

    return res;
}

dvec std_solve(const dmat &a, const dvec& b) {
    dvec res(a.size(), 0.0);

    dvec r(b);
    dvec p(r);

    #ifdef DEBUG
    double begin = omp_get_wtime();
    #endif

    for (int i = 0; i < a.size(); i++) {
        dvec r_prev;
        dvec mv = std_matrix_vec(a, p);
        r_prev = r;

        double d = std_vec_vec(r, r) / std::max(vec_vec(p, mv), SMOL);
        res = vec_vec_comb(1.0, res, d, p);
        r = vec_vec_comb(1.0, r, -d, mv);

        if (vec_norm(r) < SMOL) break;

        double s = vec_vec(r, r) /
                std::max(vec_vec(r_prev, r_prev), SMOL);
        p = vec_vec_comb(1.0, r, s, p);
    }

    #ifdef DEBUG
    double end = omp_get_wtime();
    std::cout << "PRALLEL TIME " << (end - begin) << std::endl;
    #endif

    return res;
}
