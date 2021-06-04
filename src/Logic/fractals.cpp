
#include <vector>
#include <string>
#include <map>
#include "generators.h"
#include "src/Logic/fractal.h"

using namespace std;

const map<string, Generator*> Fractal::fractals = {
        {
            "Mandelbrot",
            new ComplexSeriesFractal([](complex<double> zn, double x, double y) { return zn*zn + complex<double>(x,y); })
        },
        {
            "Tricorn",
            new ComplexSeriesFractal([](complex<double> zn, double x, double y) { return pow(conj(zn), 2) + complex<double>(x,y);})
        },
        {
            "Julia Set (-0.835 - 0.2325i)",
            new ComplexSeriesFractal([](complex<double> zn, double x, double y) { return pow(zn, 2) + complex<double>(-0.835,-0.2325);})
        },
        {
            "Custom1",
            new ComplexSeriesFractal([](complex<double> zn, double x, double y) { return pow(zn, 2) - pow(zn,3) + complex<double>(-0.372,0.519);})
        }
};
