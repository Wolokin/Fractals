#include "generators.h"

auto f(complex<double> d) {
    return pair(pow(d, 3) - 1.0, pow(d, 2));
}

rgb Newton::getColor(double x, double y) {
    complex<double> d = boost::math::tools::complex_newton(f, complex<double>(x,y));
    complex<double> eval = f(d).first;
    auto norm = abs(eval);
    if(isnan(norm) or norm > eps) return array<rgb_value_type, 3>();
    int c = isClose(d);
    if(c != -1) return array<rgb_value_type, 3>();
    roots.push_back(d);
    return array<rgb_value_type, 3>();
}

size_t Newton::isClose(complex<double> d) {
    for(size_t i = 0; i < roots.size(); ++i) {
        if(abs(d-roots[i]) < eps) return i + 1;
    }
    return -1;
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
    complex<double> zn(x,y);
    size_t i = 0;
    while(i < maxiter && abs(zn) < 2) {
        zn = f(zn,x,y);
        ++i;
    }
    return palette.getColor(i);
}