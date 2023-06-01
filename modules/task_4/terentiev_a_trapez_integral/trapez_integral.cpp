// Copyright 2023 Terentiev Alexander
#include "../../../modules/task_4/terentiev_a_trapez_integral/trapez_integral.h"

#include <vector>
#include "../../../3rdparty/unapproved/unapproved.h"

double Func1(double x, double y, double z) { return x * y * z; }

double Func2(double x, double y, double z) { return 1 / (x * y * z); }

bool Testing(double fromX, double fromY, double fromZ, double toX, double toY,
             double toZ, double (*integrateFunc)(double, double, double),
             double trueRes) {
    double trapezRes = TrapezIntegral3D(fromX, fromY, fromZ, toX, toY, toZ,
                                        Steps, integrateFunc);
    std::cout << trapezRes << " " << trueRes;
    return Compare(trapezRes, trueRes);
}

bool Compare(double a, double b) { return abs(a - b) < MaxError; }

double TrapezIntegral3D(double fromX, double fromY, double fromZ, double toX,
                        double toY, double toZ, int steps,
                        double (*func)(double, double, double)) {
    double lx = toX - fromX;
    double ly = toY - fromY;
    double lz = toZ - fromZ;

    double dx = lx / steps;
    double dy = ly / steps;
    double dz = lz / steps;

    double result = 0;

    for (int stepX = 0; stepX < steps; stepX++)
        for (int stepY = 0; stepY < steps; stepY++)
            for (int stepZ = 0; stepZ < steps; stepZ++) {
                double xPrev = fromX + dx * stepX;
                double yPrev = fromY + dy * stepY;
                double zPrev = fromZ + dz * stepZ;

                double xNext = fromX + dx * (stepX + 1);
                double yNext = fromY + dy * (stepY + 1);
                double zNext = fromZ + dz * (stepZ + 1);

                result +=
                    dx * dy * dz *
                    (func(xPrev, yPrev, zPrev) + func(xNext, yNext, zNext)) / 2;
            }

    return result;
}

static void doCalc(double fromX, double dx, double stepX,
                   double fromY, double dy, double stepY,
                   double fromZ, double dz, double stepZ,
                   double (*func)(double, double, double),
                   std::vector<double>* results) {
    double xPrev = fromX + dx * stepX;
    double yPrev = fromY + dy * stepY;
    double zPrev = fromZ + dz * stepZ;

    double xNext = fromX + dx * (stepX + 1);
    double yNext = fromY + dy * (stepY + 1);
    double zNext = fromZ + dz * (stepZ + 1);

    (*results)[stepZ] = 0;
    (*results)[stepZ] =
        dx * dy * dz *
        (func(xPrev, yPrev, zPrev) + func(xNext, yNext, zNext)) / 2;
}

double TrapezIntegral3DParallel(double fromX, double fromY, double fromZ,
                                double toX, double toY, double toZ, int steps,
                                double (*func)(double, double, double)) {
    const double lx = toX - fromX;
    const double ly = toY - fromY;
    const double lz = toZ - fromZ;

    const double dx = lx / steps;
    const double dy = ly / steps;
    const double dz = lz / steps;

    double result = 0;

    size_t num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_threads);

    for (int stepX = 0; stepX < steps; stepX++)
        for (int stepY = 0; stepY < steps; stepY++) {
            std::vector<double> results(steps);
            size_t chunk_size = steps / num_threads;
            size_t suffix = steps % num_threads;
            for (size_t i = 0; i < num_threads; i++) {
                threads[i] = std::thread([&](size_t start, size_t end) {
                    for (int stepZ = start; stepZ < end; stepZ++) {
                        doCalc(fromX, dx, stepX, fromY, dy, stepY, fromZ, dz, stepZ, func, &results);
                    }
                }, i * chunk_size, (i + 1) * chunk_size);
            }

            for (size_t stepZ = steps - suffix; stepZ < steps; stepZ++) {
                doCalc(fromX, dx, stepX, fromY, dy, stepY, fromZ, dz, stepZ, func, &results);
            }

            for (auto& t : threads) {
                t.join();
            }
            for (double res : results) {
                result += res;
            }
        }

    return result;
}
