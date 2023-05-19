// Copyright 2023 Mironov Nikita
#include "../../../modules/task_2/mironov_n_trapezoid_method_omp/trapezoid.h"

double trapezoid_method(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int N) {

    double h_for_x = (bounds[0].second - bounds[0].first) / N;
    double h_for_y = (bounds[1].second - bounds[1].first) / N;
    double h_for_z = (bounds[2].second - bounds[2].first) / N;

    double result = 0;

    #pragma omp parallel for reduction(+: result)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int s = 0; s < N; m++) {
                    double x_start = bounds[0].first + i * h_for_x;
                    double x_end = bounds[0].first + (i + 1) * h_for_x;

                    double y_start = bounds[1].first + j * h_for_y;
                    double y_end = bounds[1].first + (j + 1) * h_for_y;

                    double z_start = bounds[2].first + s * h_for_z;
                    double z_end = bounds[2].first + (s + 1)* h_for_z;

                    result +=
                    0.5 * (x_end - x_start) *
                    (y_end - y_start) *
                    (z_end - z_start) *
                    (f({x_start, y_start, z_start}) + f({x_end, y_end, z_end}));
                }
            }
        }
    return result;
}
