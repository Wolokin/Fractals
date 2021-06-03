
// palettes copied from https://github.com/jgreitemann/colormap/blob/master/include/colormap/palettes.hpp

#include <vector>
#include <string>
#include <map>
#include "generators.h"
#include "oglwidget.h"

using namespace std;

const map<string, Generator*> OGLWidget::fractals = {
        {
            "Mandelbrot",
            new Mandelbrot
        },
        {
            "Tricorn",
            new Tricorn
        }
};
