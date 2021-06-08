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

/* Abstract base generator class
 * It contains one pure virtual method that needs to be implemented: getColor
 * Apart from that, it defines some basic operations on generators*/
class Generator {
protected:
    int maxiter = default_maxiter;
    int miniter = default_miniter;
    colorPalette palette;
public:
    Generator() : palette(default_palette, miniter, maxiter) {}

    virtual ~Generator() = default;

    virtual rgb getColor(double x, double y) = 0;

    virtual bool needsUpdate() { return false; }
    virtual void updateDone() {}

    virtual void reset() {};
    virtual void resetIntervals(double &x1, double &x2, double &y1, double &y2);

    void increaseMaxIter();
    void decreaseMaxIter();
    void increaseMinIter();
    void decreaseMinIter();

    void setPalette(string s) { palette = colorPalette(std::move(s), miniter, maxiter); }
};

/* Just a basic generalized Newton fractal generator.
 * It takes the complex function and its first derivative*/
class Newton : public Generator {
    // mutex for push_back of new roots
    mutex mut;
    vector<complex<double>> roots;

    int whichRoot(complex<double> d);
    static bool isZero(complex<double> c) { return abs(c) < eps; }
    complex<double> newtonRaphson(complex<double> guess, int &iter);

    complex<double> (*f)(complex<double>);
    complex<double> (*df)(complex<double>);
    double a;

    bool updated = false;

public:
    Newton(complex<double> (*f)(complex<double>), complex<double> (*df)(complex<double>), double a = 1);

    rgb getColor(double x, double y) override;
    void reset() override { roots.clear(); };
    bool needsUpdate() override { return updated; };
    void updateDone() override { updated = false; }
};

/* Base class for all fractals created according to
 the speed of convergence of a complex series (escape-time fractals).
 The general equation is z_n+1 = f(z_n,x,y)
 and the point (x,y) is colored in regards to
 iterations needed for it to exceed an abs value of 2
 template<complex<double> (*F)(complex<double>, double, double)> */
class ComplexSeriesFractal : public Generator {
    complex<double> (*f)(complex<double>, double, double);

public:
    explicit ComplexSeriesFractal(complex<double> (*f)(complex<double>, double, double)) : f{f} {}

    rgb getColor(double x, double y) override;
};


#endif //FRACTALS_GENERATORS_H
