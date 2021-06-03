
#include <vector>
#include <string>
#include <map>
#include "generators.h"
#include "src/OpenGL/oglwidget.h"

using namespace std;

const map<string, Generator*> OGLWidget::fractals = {
        {
            "Mandelbrot",
            new ComplexSeriesFractal([](complex<double> zn, double x, double y) { return zn*zn + complex<double>(x,y); })
        },
        {
            "Tricorn",
            new ComplexSeriesFractal([](complex<double> zn, double x, double y) { return pow(conj(zn), 2) + complex<double>(x,y);})
        }
};
