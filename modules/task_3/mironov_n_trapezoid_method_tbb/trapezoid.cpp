// Copyright 2023 Mironov Nikita
#include "../../../modules/task_3/mironov_n_trapezoid_method_tbb/trapezoid.h"

class d1_functor {
 private:
    double h;
    double boundX;
    double result;
    double (*f)(std::vector<double>);

 public:
    explicit d1_functor(double _h, double _boundX,
    double (*_f)(std::vector<double>)):
    h(_h), boundX(_boundX), result(0), f(_f) {}

    d1_functor(const d1_functor& funct, tbb::split): h(funct.h),
    boundX(funct.boundX), result(0), f(funct.f) {}

    void operator()(const tbb::blocked_range<int>& r) {
        int i = r.begin();
        int end = r.end();

        double x = 0;

        for (i = r.begin(); i < end; i++) {
            x = boundX + h * i;
            result += h * f({x});
        }
    }

    void join(const d1_functor& funct) {
    result += funct.result;
    }

    double get_result() {
        return result;
    }
};

class d2_functor{
 private:
    double hx, hy;
    const std::vector<std::pair<double, double>>& bounds;
    double result;
    double (*f)(std::vector<double>);

 public:
    explicit d2_functor(double _hx, double _hy,
    const std::vector<std::pair<double, double>>& _bounds,
    double (*_f)(std::vector<double>)):
    hx(_hx), hy(_hy), bounds(_bounds), result(0), f(_f) {}

    d2_functor(const d2_functor& funct, tbb::split): hx(funct.hx), hy(funct.hy),
    bounds(funct.bounds), result(0), f(funct.f) {}

    void operator()(const tbb::blocked_range2d<int>& r) {
        int i = r.rows().begin();
        int I_end = r.rows().end();

        int j = r.cols().begin();
        int J_end = r.cols().end();

        double x = 0;
        double y = 0;

        for (i = r.rows().begin(); i < I_end; i++) {
            x = bounds[0].first + hx * i;
            result += 0.5 * (f({x, bounds[1].first}) +
            f({x, bounds[1].second}));

            y = bounds[1].first + hy * i;

            result += 0.5 * (f({bounds[0].first, y}) +
            f({bounds[0].second, y}));
            for (int j = r.cols().begin(); j < J_end; j++) {
                y = bounds[1].first + hy * j;

                result += f({x, y});
            }
        }
    }

    void join(const d2_functor& funct) {
    result += funct.result;
    }

    double get_result() {
        return result;
    }
};

class d3_functor{
 private:
    double hx, hy, hz;
    const std::vector<std::pair<double, double>>& bounds;
    double result;
    double (*f)(std::vector<double>);

 public:
    explicit d3_functor(double _hx, double _hy, double _hz,
    const std::vector<std::pair<double, double>>& _bounds,
    double (*_f)(std::vector<double>)):
    hx(_hx), hy(_hy), hz(_hz), bounds(_bounds), result(0), f(_f) {}

    d3_functor(const d3_functor& funct, tbb::split): hx(funct.hx), hy(funct.hy), hz(funct.hz),
    bounds(funct.bounds), result(0), f(funct.f) {}

    void operator()(const tbb::blocked_range3d<int>& r) {
        int i = r.pages().begin();
        int I_end = r.pages().end();

        int j = r.rows().begin();
        int J_end = r.rows().end();

        int s = r.cols().begin();
        int S_end = r.cols().end();

        double x = 0;
        double y = 0;
        double z = 0;

        for (i = r.pages().begin(); i < I_end; i++) {
            x = bounds[0].first + hx * i;
            y = bounds[1].first + hy * i;
            z = bounds[2].first + hz * i;

            result += 0.25 *
            (f({x, bounds[1].first, bounds[2].first}) +
            f({x, bounds[1].second, bounds[2].second}));

            result += 0.25 *
            (f({bounds[0].first, y, bounds[2].first}) +
            f({bounds[0].second, y, bounds[2].second}));

            result += 0.25 *
            (f({bounds[0].first, bounds[1].first, z}) +
            f({bounds[0].second, bounds[1].second, z}));
            for (j = r.rows().begin(); j < J_end; j++) {
                x = bounds[0].first + hx * i;
                z = bounds[2].first + hz * j;

                result += 0.5 * (f({x, bounds[1].first, z}) +
                f({x, bounds[1].second, z}));

                y = bounds[1].first + hy * i;

                result += 0.5 * (f({bounds[0].first, y, z}) +
                f({bounds[0].second, y, z}));

                y = bounds[1].first + hy * j;

                result += 0.5 * (f({x, y, bounds[2].first}) +
                f({x, y, bounds[2].second}));

                for (s = r.cols().begin(); s < S_end; s++) {
                    z = bounds[2].first + hz * s;

                    result += f({x, y, z});
                }
            }
        }
    }

    void join(const d3_functor& funct) {
    result += funct.result;
    }

    double get_result() {
        return result;
    }
};

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
        double h = (bounds[0].second-bounds[0].first)/N;

        d1_functor d1(h, bounds[0].first, f);
        tbb::parallel_reduce(tbb::blocked_range<int>(0, N), d1);
        double res = d1.get_result();
        res += (h/2.0) * (f({bounds[0].first}) + f({bounds[0].second}));
        return res;
    }
    if (dimensions == 2) {
        double hx = (bounds[0].second-bounds[0].first)/N;
        double hy = (bounds[1].second-bounds[1].first)/N;

        d2_functor d2(hx, hy, bounds, f);
        tbb::parallel_reduce(tbb::blocked_range2d<int>(0, N, 0, N), d2);
        double res = d2.get_result();
        res += 0.25 *
        (f({bounds[0].first, bounds[1].first}) +
        f({bounds[0].second, bounds[1].second}) +
        f({bounds[0].first, bounds[1].second}) +
        f({bounds[0].second, bounds[1].first}));
        res = res * hx * hy;
        return res;
    }
    if (dimensions == 3) {
        double hx = (bounds[0].second-bounds[0].first)/N;
        double hy = (bounds[1].second-bounds[1].first)/N;
        double hz = (bounds[2].second-bounds[2].first)/N;

        d3_functor d3(hx, hy, hz, bounds, f);
        tbb::parallel_reduce(tbb::blocked_range3d<int>(0, N, 0, N, 0, N), d3);
        double res = d3.get_result();
        res += 0.125 *
        (f({bounds[0].first, bounds[1].first, bounds[2].first}) +
        f({bounds[0].first, bounds[1].second, bounds[2].first}) +
        f({bounds[0].first, bounds[1].first, bounds[2].second}) +
        f({bounds[0].first, bounds[1].second, bounds[2].second}) +
        f({bounds[0].second, bounds[1].first, bounds[2].first}) +
        f({bounds[0].second, bounds[1].second, bounds[2].first}) +
        f({bounds[0].second, bounds[1].first, bounds[2].second}) +
        f({bounds[0].second, bounds[1].second, bounds[2].second}));
        res = res * hx * hy * hz;
        return res;
    }
    return 0;
}
