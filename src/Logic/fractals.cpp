
#include <vector>
#include <string>
#include <map>
#include "generators.h"
#include "src/Logic/fractal.h"

using namespace std;

const map<string, Generator *> Fractal::fractals = {
        {
                "Mandelbrot",
                new ComplexSeriesFractal([](complex<double> zn, double x, double y) {
                    return zn * zn + complex<double>(x, y);
                })
        },
        {
                "Tricorn",
                new ComplexSeriesFractal([](complex<double> zn, double x, double y) {
                    return pow(conj(zn), 2) + complex<double>(x, y);
                })
        },
        {
                "Julia Set (z^2, -0.835 - 0.2325i)",
                new ComplexSeriesFractal([](complex<double> zn, double x, double y) {
                    return pow(zn, 2) + complex<double>(-0.835, -0.2335);
                })
        },
        {
                "Julia Set (z^3, -0.535 - 0.1325i)",
                new ComplexSeriesFractal([](complex<double> zn, double x, double y) {
                    return pow(zn, 3) + complex<double>(-0.535, -0.1325);
                })
        },
        {
                "Julia Set (z^2 - z^3)",
                new ComplexSeriesFractal([](complex<double> zn, double x, double y) {
                    return pow(zn, 2) - pow(zn, 3) + complex<double>(-0.372, 0.519);
                })
        },
        {
                "Neuron",
                new ComplexSeriesFractal([](complex<double> zn, double, double) {
                    return pow(complex(-zn.imag(), -zn.real()), 2) + zn;
                })
        },
//        {
//                "Custom2",
//                new ComplexSeriesFractal([](complex<double> zn, double, double) {
//                    return zn - (pow(zn, 3) + 1.0) / (3.0 * pow(zn, 2));
//                })
//        },
        {
                "Newton (z^3 - 1)",
                new Newton([](complex<double> z) { return pow(z, 3) + 1.0; },
                           [](complex<double> z) { return 2.0 * pow(z, 2); })
        },
        {
                "Newton (sin(z))",
                new Newton([](complex<double> z) { return sin(z); },
                           [](complex<double> z) { return cos(z); })
        },
        {
                "Newton (z^(4+3i) - 1)",
                new Newton([](complex<double> z) { return pow(z, complex(4.0, 3.0)) - 1.0; },
                           [](complex<double> z) { return complex(4.0, 3.0) * pow(z, complex(3.0, 3.0)); })
        },
        {
                "Newton (cosh(z))",
                new Newton([](complex<double> z) { return cosh(z); },
                           [](complex<double> z) { return sinh(z); })
        },
        {
                "Burning Ship",
                new ComplexSeriesFractal([](complex<double> zn, double x, double y) {
                    return pow(complex(abs(zn.real()), abs(zn.imag())), 2) + complex(x,y);
                })
        },
};
