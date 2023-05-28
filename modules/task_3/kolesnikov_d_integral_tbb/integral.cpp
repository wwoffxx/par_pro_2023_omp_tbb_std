// Copyright 2023 Kolesnikov Denis
#include "../../../modules/task_3/kolesnikov_d_integral_tbb/integral.h"

class MyFunctor {
 private:
    double hx, hy, hz;
    double a, b, c;
    double res;
    double (*func)(std::vector<double>);

 public:
    explicit MyFunctor(
      double _hx,
      double _hy,
      double _hz,
      double _a,
      double _b,
      double _c,
      double (*_func)(std::vector<double>))
        : hx(_hx), hy(_hy), hz(_hz), a(_a), b(_b), c(_c), res(0), func(_func) {}

    MyFunctor(const MyFunctor& f, tbb::split)
      :  hx(f.hx), hy(f.hy), hz(f.hz),
    a(f.a), b(f.b), c(f.c), res(0), func(f.func) {}

    void operator()(const tbb::blocked_range3d<int>& r) {
        int i = r.pages().begin(), i_end = r.pages().end();
        int j = r.rows().begin(), j_end = r.rows().end();
        int m = r.cols().begin(), m_end = r.cols().end();

        for (i = r.pages().begin(); i < i_end; i++) {
          for (j = r.rows().begin(); j < j_end; j++) {
            for (m = r.cols().begin(); m < m_end; m++) {
              const double x1 = a + i*hx;
              const double x2 = a + (i+1)*hx;
              const double y1 = b + j*hy;
              const double y2 = b + (j+1)*hy;
              const double z1 = c + m*hz;
              const double z2 = c + (m+1)*hz;
              res+=
                0.5*(x2-x1)*(y2-y1)*(z2-z1)*
                  (func({x1, y1, z1}) + func({x2, y2, z2}));
            }
          }
        }
    }
    void join(const MyFunctor& f) {
        res += f.res;
    }
    double result() {
        return res;
    }
};

double integral(
  const std::vector<std::pair<double, double>>& bounds,
  int n,
  double (*func)(std::vector<double>)) {
    double hx = (bounds[0].second - bounds[0].first) / n;
    double hy = (bounds[1].second - bounds[1].first) / n;
    double hz = (bounds[2].second - bounds[2].first) / n;
    double a = bounds[0].first;
    double b = bounds[1].first;
    double c = bounds[2].first;

    MyFunctor ftr(hx, hy, hz, a, b, c, func);
    tbb::parallel_reduce(tbb::blocked_range3d<int>(0, n, 0, n, 0, n), ftr);
    return ftr.result();
}
