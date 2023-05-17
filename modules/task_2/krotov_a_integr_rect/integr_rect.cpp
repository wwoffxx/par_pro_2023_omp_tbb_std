// Copyright 2023 Krotov Aleksey
#include "../../../modules/task_2/krotov_a_integr_rect/integr_rect.h"

double Integrate(size_t dim, double* step, double* lower, double* upper,
                 Function func) {
    double result = 0;
    int total = 1;
    auto size = new int[dim];
    for (size_t k = 0; k < dim; ++k)
        total *= size[k] = static_cast<int>((upper[k] - lower[k]) / step[k]);

    #pragma omp parallel shared(total, size)
    {
        auto curr_point = new double[dim];
        int j;

        #pragma omp for reduction(+ : result)
            for (int i = 0; i < total; ++i) {
                j = i;
                for (size_t k = 0; k < dim; ++k) {
                    curr_point[k] =
                        lower[k] + static_cast<double>(j % size[k]) * step[k];
                    j /= size[k];
                }
                result += func(curr_point);
            }
            delete[] curr_point;
    }

    for (size_t k = 0; k < dim; ++k)
        result *= step[k];

    delete[] size;
    return result;
}
