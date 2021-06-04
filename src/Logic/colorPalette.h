//
// Created by filip on 30.05.2021.
//

#ifndef FRACTALS_COLORPALETTE_H
#define FRACTALS_COLORPALETTE_H

#include <map>
#include <string>
#include <vector>
#include "constants.h"
#include "palettes.h"
#include <iostream>

using namespace std;

class colorPalette {
    string paletteName;
    vector<rgb> palette;
    double start, end;
    double step;
public:
    colorPalette(string paletteName, double left, double right);
    rgb getColor(double x);
    void resize(double left, double right);
    //void next();
    //void previous();
};

#endif //FRACTALS_COLORPALETTE_H
