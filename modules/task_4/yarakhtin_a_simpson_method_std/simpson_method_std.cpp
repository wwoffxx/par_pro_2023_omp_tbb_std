// Copyright 2023 Yarakhtin Anton
#include<cmath>
#include "../../../modules/task_4/yarakhtin_a_simpson_method_std/simpson_method_std.h"
#include "../../../3rdparty/unapproved/unapproved.h"

double simpson_method(std::vector<std::tuple<double, double, int>> scopes,
    std::function<double(const std::vector<double>&)> func) {
    int dim = scopes.size();
    std::vector<double> h(dim);
    int points_count = 1;
    double main_coef = 1.;
    for (int i = 0; i < dim; i++) {
        int partions = std::get<2>(scopes[i]);
        points_count *= (1 + 2 * partions);
        h[i] = (std::get<1>(scopes[i]) - std::get<0>(scopes[i])) / (2. * partions);
        main_coef *= h[i] / 3.;
    }

    double result = 0;
    std::vector<double> func_args(dim);
    for (int i = 0; i < points_count; i++) {
        int coef = 1;
        for (int j = 0, tmp = i; j < dim; j++) {
            int points = (1 + 2 * std::get<2>(scopes[j]));
            int index = tmp % points;
            tmp /= points;
            func_args[j] = std::get<0>(scopes[j]) + index * h[j];
            if (index != 0 && index != points - 1) {
                coef *= 2 * (1 + index % 2);
            }
        }
        result += coef * func(func_args);
    }
    return main_coef * result;
}

double simpson_method_std(std::vector<std::tuple<double, double, int>> scopes,
    std::function<double(const std::vector<double>&)> func) {
    int dim = scopes.size();
    std::vector<double> h(dim);
    int points_count = 1;
    double main_coef = 1.;
    for (int i = 0; i < dim; i++) {
        int partions = std::get<2>(scopes[i]);
        points_count *= (1 + 2 * partions);
        h[i] = (std::get<1>(scopes[i]) - std::get<0>(scopes[i])) / (2. * partions);
        main_coef *= h[i] / 3.;
    }

    int chunk_size = std::max(1024, static_cast<int>(sqrt(points_count)));
    int chunk_count = points_count / chunk_size + (points_count % chunk_size ? 1 : 0);

    double result = 0;
    std::vector<std::thread> threads;
    std::vector<double> loc_results(chunk_count, 0);
    for (int k = 0; k < chunk_count; k++) {
        std::thread th([k, chunk_size, points_count, &h, &result, &scopes, &loc_results, &func]() {
            for (int i = k * chunk_size; i < (k + 1) * chunk_size && i < points_count; i++) {
                std::vector<double> func_args(scopes.size());
                int coef = 1;
                for (int j = 0, tmp = i; j < scopes.size(); j++) {
                    int points = (1 + 2 * std::get<2>(scopes[j]));
                    int index = tmp % points;
                    tmp /= points;
                    func_args[j] = std::get<0>(scopes[j]) + index * h[j];
                    if (index != 0 && index != points - 1) {
                        coef *= 2 * (1 + index % 2);
                    }
                }
                loc_results[k] += coef * func(func_args);
            }
            });
        threads.push_back(std::move(th));
    }
    for (int k = 0; k < chunk_count; k++) {
        threads[k].join();
        result += loc_results[k];
    }

    return main_coef * result;
}
