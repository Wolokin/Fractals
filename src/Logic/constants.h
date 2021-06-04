#ifndef FRACTALS_CONSTANTS_H
#define FRACTALS_CONSTANTS_H

#include <cstdlib>
#include <array>
#include <iostream>
#include <string>

const size_t pixel_data_len = 3;

// epsilon
const double eps = 1e-8;

// rgb representation
using rgb_value_type = float;
using rgb = std::array<rgb_value_type, 3>;

// default fractal
const std::string default_fractal = "Mandelbrot";

// default palette
const std::string default_palette = "inferno";

#endif //FRACTALS_CONSTANTS_H
