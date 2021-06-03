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

using namespace std;

// Abstract base generator class
class Generator {
protected:
    size_t maxiter = 60;
    static const int maxIterChangeStep = 10;
    colorPalette palette;
public:
    Generator() : palette("inferno", 0, maxiter) {}
    virtual ~Generator() = default;
    virtual array<rgb_value_type, 3> getColor(double x, double y) = 0;
    virtual void setStartingIntervals(double &x1, double &x2, double &y1, double &y2) {
        x1 = -2.5; x2 = 2.5; y1 = -2.5; y2 = 2.5;
    }
    void increaseMaxIter() { maxiter += maxIterChangeStep; palette.resize(0, maxiter); }
    void decreaseMaxIter() { maxiter -= maxIterChangeStep; palette.resize(0, maxiter); }
    void setPalette(string& s) { palette = colorPalette(s, 0, maxiter); }
    void nextPalette() { palette.next(); }
    void previousPalette() { palette.previous(); }
};

// Newton fractal
class Newton : public Generator {
    vector<complex<double>> roots;
    size_t isClose(complex<double>);
public:
    rgb getColor(double x, double y) override;
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
