#include "generators.h"

rgb Newton::getColor(double x, double y) {
    // std::function func = [this](complex<double> d) { return pair(this->f(d), this->df(d)); };
    //complex<double> d = boost::math::tools::complex_newton(func, complex<double>(x, y));
    int iter;
    complex<double> d = newtonRaphson(complex(x,y), iter);
    double index = whichRoot(d);
    return palette.getColor(index*(maxiter)/(roots.size()) + (double)iter/roots.size());
}

int Newton::whichRoot(complex<double> d) {
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

complex<double> Newton::newtonRaphson(complex<double> guess, int &iter) {
    for(iter = 0; iter < maxiter; ++iter) {
        complex<double> eval = f(guess);
        if(abs(eval) < eps) {
            break;
        }
        guess = guess - a*eval/df(guess);
    }
    return guess;
}

void Newton::reset() {
    roots.clear();
}

//rgb Mandelbrot::getColor(double x, double y) {
//    complex<double> z(0,0);
//    complex<double> c(x,y);
//    size_t i = 0;
//    while(i < maxiter && abs(z) < 2) {
//        z = z*z + c;
//        ++i;
//    }
//    return palette.getColor(i);
//}

//rgb JuliaSet::getColor(double x, double y) {
//    complex<double> z(0,0);
//    complex<double> c(x,y+0.8);
//    size_t i = 0;
//    while(i < maxiter && abs(z) < 2) {
//        z = z*z + pow(c,exp);
//        ++i;
//    }
//    return palette.getColor(i);
//}

rgb ComplexSeriesFractal::getColor(double x, double y) {
    complex<double> zn(x, y);
    int i = 0;
    while (i < maxiter && abs(zn) < 2) {
        zn = f(zn, x, y);
        ++i;
    }
    return palette.getColor(max(i, miniter));
}