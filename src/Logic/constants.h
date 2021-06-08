#ifndef FRACTALS_CONSTANTS_H
#define FRACTALS_CONSTANTS_H

#include <cstdlib>
#include <array>
#include <iostream>
#include <string>

using namespace std;

// how many components are there in the color representation
// (i.e. RGB has 3 components, RGBA has 4, etc.)
const size_t pixel_data_len = 3;
// rgb representation
using rgb_value_type = float;
using rgb = array<rgb_value_type, pixel_data_len>;

// default displayed fractal
const string default_fractal = "Mandelbrot";

// default displayed palette
const string default_palette = "inferno";

// rate at which maximum iterations are changed
const int iter_change_step = 10;
const int default_maxiter = 60;
const int default_miniter = 0;

// fractal starting domain
const double sx1 = -2.5, sx2 = 2.5, sy1 = -2.5, sy2 = 2.5;

// epsilon used in calculating roots for newton fractals
const double eps = 1e-8;
// ratio at which zooming changes the plot area
const double zoom_ratio = 0.9;
// number of threads used in fractal calculations
const int thread_count = 20;
// ratio at which expanding and dexpanding works
const double expand_ratio = 0.1;

// refresh time - delay in ms between frames
const size_t refresh_time = 30;

#endif //FRACTALS_CONSTANTS_H
