#ifndef FRACTALS_CONSTANTS_H
#define FRACTALS_CONSTANTS_H

#include <cstdlib>
#include <array>

// Initial window size
const size_t windowWidth = 800;
const size_t windowHeight = 800;

// Initial window position
const size_t windowXPos = 100;
const size_t windowYPos = 100;

const size_t pixelDataLen = 3;

// epsilon
const double eps = 1e-8;

// rgb representation
using rgb_value_type = float;
using rgb = std::array<rgb_value_type, 3>;

#endif //FRACTALS_CONSTANTS_H
