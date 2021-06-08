#ifndef FRACTALS_COLORPALETTE_H
#define FRACTALS_COLORPALETTE_H

#include <map>
#include <string>
#include <vector>
#include "constants.h"
#include "palettes.h"
#include <iostream>

/* This class supplies a continuous color palette based on a few interpolation nodes
 * defined in palettes.h*/
class colorPalette {
    string paletteName;
    vector<rgb> palette;
    double start, end;
    double step;
public:
    colorPalette(string paletteName, double left, double right);
    /* Returns rgb values of a color that lies on position 'x'
     * in the interpolated space between 'start' and 'end'*/
    rgb getColor(double x);
    /* Changes left and right limit of the palette*/
    void resize(double left, double right);
};

#endif //FRACTALS_COLORPALETTE_H
