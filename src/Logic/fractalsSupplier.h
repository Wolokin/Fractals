#ifndef FRACTALS_FRACTALSSUPPLIER_H
#define FRACTALS_FRACTALSSUPPLIER_H

/* This class is used only as a supplier of fractals based on their names
 * If you want to define your own escape-time fractal - this is the place.
 * All you need to do is define a new EscapeTimeFractal or NewtonFractal map entry */
class FractalsSupplier {
public:
    const map<string, Generator *> fractals;
    FractalsSupplier(): fractals{
            {
                    "Mandelbrot",
                    new EscapeTimeFractal([](complex<double> zn, double x, double y) {
                        return zn * zn + complex<double>(x, y);
                    })
            },
            {
                    "Tricorn",
                    new EscapeTimeFractal([](complex<double> zn, double x, double y) {
                        return pow(conj(zn), 2) + complex<double>(x, y);
                    })
            },
            {
                    "Julia Set (z^2, -0.835 - 0.2325i)",
                    new EscapeTimeFractal([](complex<double> zn, double, double) {
                        return pow(zn, 2) + complex<double>(-0.835, -0.2335);
                    })
            },
            {
                    "Julia Set (z^3, -0.535 - 0.1325i)",
                    new EscapeTimeFractal([](complex<double> zn, double, double) {
                        return pow(zn, 3) + complex<double>(-0.535, -0.1325);
                    })
            },
            {
                    "Julia Set (z^2 - z^3)",
                    new EscapeTimeFractal([](complex<double> zn, double, double) {
                        return pow(zn, 2) - pow(zn, 3) + complex<double>(-0.372, 0.519);
                    })
            },
            {
                    "Neuron",
                    new EscapeTimeFractal([](complex<double> zn, double, double) {
                        return pow(complex(-zn.imag(), -zn.real()), 2) + zn;
                    })
            },
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
                    new EscapeTimeFractal([](complex<double> zn, double x, double y) {
                        return pow(complex(abs(zn.real()), abs(zn.imag())), 2) + complex(x,y);
                    })
            },
            {
                    "Newton (z^8 + 15z^4 - 16)",
                    new Newton([](complex<double> z) { return pow(z,8) + 15.0*pow(z,4) - 16.0; },
                               [](complex<double> z) { return 8.0*pow(z,7) + 60.0*pow(z,3); })
            },
    } {}

    ~FractalsSupplier() { for(const auto& it : fractals) delete it.second; }
};

#endif //FRACTALS_FRACTALSSUPPLIER_H
