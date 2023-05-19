// Copyright 2023 Mironov Nikita
#include "../../../modules/task_3/mironov_n_trapezoid_method_tbb/trapezoid.h"

double trapezoid_method(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int N) {

    double h_for_x = (bounds[0].second - bounds[0].first) / N;
    double h_for_y = (bounds[1].second - bounds[1].first) / N;
    double h_for_z = (bounds[2].second - bounds[2].first) / N;

    double result = 0;

    tbb::parallel_for(tbb::blocked_range3d<int>(0, N, 0, N, 0, N),
            [&](tbb::blocked_range3d<int> r) {
        int i_end = r.pages().end();
        int j_end = r.rows().end();
        int s_end = r.cols().end();

        for (int i = r.pages().begin(); i < i_end; i++) {
            for (int j = r.rows().begin(); j < j_end; j++) {
                for (int s = r.cols().begin(); s < s_end; s++) {
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
    });
    return result;
}
