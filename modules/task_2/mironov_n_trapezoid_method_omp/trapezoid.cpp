// Copyright 2023 Mironov Nikita
#include "../../../modules/task_2/mironov_n_trapezoid_method_omp/trapezoid.h"

double d1_method_Openmp(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int N) {
    double doubleStepsCount = N;

    double h = (bounds[0].second - bounds[0].first)/doubleStepsCount;

    double x = 0;

    double result = 0;
        #pragma omp parallel for reduction(+: result)
        for (int i = 1; i < N; i++) {
            x = bounds[0].first + h * i;
            result += h * f({x});
        }

    result += (h/2.0) * (f({bounds[0].first}) + f({bounds[0].second}));

    return result;
}

double d2_method_Openmp(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int N) {
    double doubleStepsCount = N;

    double h_for_x = (bounds[0].second - bounds[0].first)/doubleStepsCount;
    double h_for_y = (bounds[1].second - bounds[1].first)/doubleStepsCount;

    double result = 0;

    double firsLoopRes = 0;
    double secondLoopRes = 0;
    #pragma omp parallel {
        #pragma omp for private(x, y) nowait reduction(+: firsLoopRes)
            for (int i = 1; i < N; i++) {
                double x = bounds[0].first + h_for_x * i;
                double y = bounds[1].first + h_for_y * i;

                    firsLoopRes += 0.5 * (f({x, bounds[1].first}) +
                    f({x, bounds[1].second}));

                    firsLoopRes += 0.5 * (f({bounds[0].first, y}) +
                    f({bounds[0].second, y}));
            }

        #pragma omp for private(x, y) collapse(2) reduction(+: secondLoopRes)
            for (int i = 1; i < N; i++) {
                for (j = 1; j <= N; j++) {
                    double x = bounds[0].first + h_for_x * i;
                    double y = bounds[1].first + h_for_y * j;

                        secondLoopRes += f({x, y});
                }
            }
    }

        result = secondLoopRes + firsLoopRes;

        result += 0.25 *
        (f({bounds[0].first, bounds[1].first}) +
        f({bounds[0].second, bounds[1].second}) +
        f({bounds[0].first, bounds[1].second}) +
        f({bounds[0].second, bounds[1].first}));

        result = result * h_for_x * h_for_y;

        return result;
}

double d3_method_Openmp(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int N) {
    double doubleStepsCount = N;

    double h_for_x = (bounds[0].second - bounds[0].first)/doubleStepsCount;
    double h_for_y = (bounds[1].second - bounds[1].first)/doubleStepsCount;
    double h_for_z = (bounds[2].second - bounds[2].first)/doubleStepsCount;

    double result = 0;

    double firstLoopRes = 0;
    double secondLoopRes = 0;
    double thirdLoopRes = 0;

    #pragma omp parallel {
        #pragma omp for nowait reduction(+: firstLoopRes)
            for (int i = 0; i < N; i++) {
                double x = bounds[0].first + h_for_x * i;
                double y = bounds[1].first + h_for_y * i;
                double z = bounds[2].first + h_for_z * i;

                    firstLoopRes += 0.25 *
                    (f({x, bounds[1].first, bounds[2].first}) +
                    f({x, bounds[1].second, bounds[2].second}));

                    firstLoopRes += 0.25 *
                    (f({bounds[0].first, y, bounds[2].first}) +
                    f({bounds[0].second, y, bounds[2].second}));

                    firstLoopRes += 0.25 *
                    (f({bounds[0].first, bounds[1].first, z}) +
                    f({bounds[0].second, bounds[1].second, z}));
            }

        #pragma omp for nowait collapse(2) reduction(+: secondLoopRes)
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    double x = bounds[0].first + h_for_x * i;
                    double y = bounds[1].first + h_for_y * i;
                    double z = bounds[2].first + h_for_z * j;

                    secondLoopRes += 0.5 * (f({x, bounds[1].first, z}) +
                    f({x, bounds[1].second, z}));

                    y = bounds[1].first + h_for_y * i;

                    secondLoopRes += 0.5 * (f({bounds[0].first, y, z}) +
                    f({bounds[0].second, y, z}));

                    y = bounds[1].first + h_for_y * j;

                    secondLoopRes += 0.5 * (f({x, y, bounds[2].first}) +
                    f({x, y, bounds[2].second}));
                }
            }

        #pragma omp for collapse(3) reduction(+: thirdLoopRes)
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    for (s = 0; s < N; s++) {
                        double x = bounds[0].first + h_for_x * i;
                        double z = bounds[2].first + h_for_z * s;
                        double y = bounds[1].first + h_for_y * j;

                        thirdLoopRes += f({x, y, z});
                    }
                }
            }
    }

        result = firstLoopRes + secondLoopRes + thirdLoopRes;

        result += 0.125 *
        (f({bounds[0].first, bounds[1].first, bounds[2].first}) +
        f({bounds[0].first, bounds[1].second, bounds[2].first}) +
        f({bounds[0].first, bounds[1].first, bounds[2].second}) +
        f({bounds[0].first, bounds[1].second, bounds[2].second}) +
        f({bounds[0].second, bounds[1].first, bounds[2].first}) +
        f({bounds[0].second, bounds[1].second, bounds[2].first}) +
        f({bounds[0].second, bounds[1].first, bounds[2].second}) +
        f({bounds[0].second, bounds[1].second, bounds[2].second}));

    result = result * h_for_x * h_for_y * h_for_z;

    return result;
}

double trapezoid_method(
    double (*f)(std::vector<double>),
    const std::vector<std::pair<double, double>>& bounds,
    int dimensions,
    int N) {
    if (dimensions != bounds.size()) {
        throw R"(The number of boundaries does not
        match the number of dimensions)";
    }

    if (dimensions == 1) {
        return d1_method_Openmp(f, bounds, N);
    }
    if (dimensions == 2) {
        return d2_method_Openmp(f, bounds, N);
    }
    if (dimensions == 3) {
        return d3_method_Openmp(f, bounds, N);
    }
    return 0;
}
