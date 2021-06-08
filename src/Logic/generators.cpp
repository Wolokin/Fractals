#include "generators.h"

void Generator::resetIntervals(double &x1, double &x2, double &y1, double &y2) {
    x1 = sx1;
    x2 = sx2;
    y1 = sy1;
    y2 = sy2;
    maxiter = default_maxiter;
    miniter = default_miniter;
}

void Generator::increaseMaxIter() {
    maxiter += iter_change_step;
    palette.resize(miniter, maxiter);
}

void Generator::decreaseMaxIter() {
    maxiter -= iter_change_step;
    palette.resize(miniter, maxiter);
}

void Generator::increaseMinIter() {
    miniter += iter_change_step;
    palette.resize(miniter, maxiter);
}

void Generator::decreaseMinIter() {
    miniter -= iter_change_step;
    palette.resize(miniter, maxiter);
}

rgb NewtonFractal::getColor(double x, double y) {
    int iter;
    complex<double> d = newtonRaphson(complex(x, y), iter);
    double index = whichRoot(d);
    return palette.getColor(index * (maxiter) / (roots.size()) + (double) iter / roots.size());
}

int NewtonFractal::whichRoot(complex<double> d) {
    if (not isZero(f(d))) return -1;
    if (not roots.empty()) {
        size_t closest = 0;
        double dist = abs(d - roots[closest]);
        size_t i;
        for (i = 1; i < roots.size(); ++i) {
            double tempDist = abs(d - roots[i]);
            if (dist > tempDist) {
                dist = tempDist;
                closest = i;
            }
        }
        if (isZero(dist)) return closest;
    }
    mut.lock();
    roots.push_back(d);
    mut.unlock();
    updated = true;
    return (int) roots.size() - 1;
}

complex<double> NewtonFractal::newtonRaphson(complex<double> guess, int &iter) {
    for (iter = 0; iter < maxiter; ++iter) {
        complex<double> eval = f(guess);
        if (abs(eval) < eps) {
            break;
        }
        guess = guess - a * eval / df(guess);
    }
    return guess;
}

NewtonFractal::NewtonFractal(complex<double> (*f)(complex<double>), complex<double> (*df)(complex<double>), double a)
        : f{f}, df{df}, a{a} {}

rgb EscapeTimeFractal::getColor(double x, double y) {
    complex<double> zn(x, y);
    int i = 0;
    while (i < maxiter && abs(zn) < 2) {
        zn = f(zn, x, y);
        ++i;
    }
    return palette.getColor(max(i, miniter));
}
