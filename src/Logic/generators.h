#ifndef FRACTALS_GENERATORS_H
#define FRACTALS_GENERATORS_H

#include <algorithm>
#include <boost/math/tools/roots.hpp>
#include <utility>
#include <vector>
#include <complex>
#include "constants.h"
#include <cstdio>
#include "colorPalette.h"
#include <string>
#include <set>
#include <mutex>

using namespace std;

// Abstract base generator class
class Generator {
protected:
    const int default_maxiter = 60;
    const int default_miniter = 0;

    constexpr static const double sx1 = -2.5, sx2 = 2.5, sy1 = -2.5, sy2 = 2.5;
    int maxiter = default_maxiter;
    int miniter = default_miniter;
    colorPalette palette;
public:
    Generator() : palette(default_palette, miniter, maxiter) {}
    virtual ~Generator() = default;
    virtual array<rgb_value_type, 3> getColor(double x, double y) = 0;
    virtual void reset() {};
    virtual bool needsUpdate() { return false; }
    virtual void updateDone() {}
    virtual void resetIntervals(double &x1, double &x2, double &y1, double &y2) {
        x1 = sx1; x2 = sx2; y1 = sy1; y2 = sy2;
        maxiter = default_maxiter;
        miniter = default_miniter;
    }
    void increaseMaxIter() { maxiter += iterChangeStep; palette.resize(miniter, maxiter); }
    void decreaseMaxIter() { maxiter -= iterChangeStep; palette.resize(miniter, maxiter); }
    void increaseMinIter() { miniter += iterChangeStep; palette.resize(miniter, maxiter); }
    void decreaseMinIter() { miniter -= iterChangeStep; palette.resize(miniter, maxiter); }
    void setPalette(string s) { palette = colorPalette(std::move(s), miniter, maxiter); }
//    void nextPalette() { palette.next(); }
//    void previousPalette() { palette.previous(); }
};

// Newton fractal
class Newton : public Generator {
    mutex mut;
    vector<complex<double>> roots;
    int whichRoot(complex<double> d);
    static bool isZero(complex<double> c) { return abs(c) < eps; }
    complex<double> (*f)(complex<double>);
    complex<double> (*df)(complex<double>);
    double a;
    bool updated = false;
    complex<double> newtonRaphson(complex<double> guess, int &iter);
public:
    Newton(complex<double> (*f)(complex<double>), complex<double> (*df)(complex<double>), double a = 1) : f{f}, df{df}, a{a} {}
    rgb getColor(double x, double y) override;
    void reset() override;
    bool needsUpdate() override { return updated; };
    void updateDone() override { updated = false; }
//    void resetIntervals(double &x1, double &x2, double &y1, double &y2) override {
//        x1 = sx1; x2 = sx2; y1 = sy1; y2 = sy2;
//        miniter = -1;
//        maxiter = (int)roots.size()-1;
//    }
};

// Base class for all fractals created according to
// the speed of convergence of a complex series.
// The general equation is z_n+1 = f(z_n,x,y)
// and the point (x,y) is colored in regards to
// iterations needed for it to exceed an abs value of 2
// template<complex<double> (*F)(complex<double>, double, double)>
class ComplexSeriesFractal : public Generator {
    complex<double> (*f)(complex<double>, double, double);
public:
    explicit ComplexSeriesFractal(complex<double> (*f)(complex<double>, double, double)) : f{f} {}
    rgb getColor(double x, double y) override;
};

// Base class for JuliaSets
// All comments to 'ComplexSeriesFractal' apply
// except that here z_n+1 = (z_n)^2 + f(z_n,x,y)
//class JuliaSet : public ComplexSeriesFractal {
//public:
//    explicit JuliaSet(const function<complex<double>(complex<double>, double, double)>& f) :
//        ComplexSeriesFractal([f](complex<double> zn, double x, double y) {return zn*zn + f(zn,x,y);}) {}
//};

// // Standard Mandelbrot set
// class Mandelbrot : public ComplexSeriesFractal {
// public:
//     Mandelbrot() : ComplexSeriesFractal([](complex<double> zn, double x, double y) { return zn*zn + complex<double>(x,y);}) {}
// };

// class Tricorn : public ComplexSeriesFractal {
// public:
//     Tricorn() : ComplexSeriesFractal([](complex<double> zn, double x, double y) { return pow(conj(zn), 2) + complex<double>(x,y);}) {}
// };

class Test : public ComplexSeriesFractal {
public:
    Test() : ComplexSeriesFractal([](complex<double> zn, double x, double y) { return zn*zn*zn + complex<double>(-0.7,0.27015);}) {}
};



#endif //FRACTALS_GENERATORS_H
