#ifndef FRACTALS_FRACTAL_H
#define FRACTALS_FRACTAL_H

#include "constants.h"
#include "generators.h"
#include <thread>

/* This class is in charge of generating a texture accepted by OpenGL.
 * Pixels are generated using getColor method defined in the 'Generator' base class.
 * It also handles logic for all operations like resizing, zooming, changing fractals
 * changing palettes etc.*/
class Fractal {
    // Current width and height in pixels
    size_t windowWidth = 0, windowHeight = 0;
    // Current palette name
    string currentPaletteName = default_palette;
    // Current pixel generator
    Generator* gen;
    // The fractal's texture. I use the fact that vector's underlying data is guaranteed to be
    // continuous after calling 'reserve'
    vector<rgb_value_type> texture;
    // Thread in charge of generating pixels
    std::thread calculationThread;
    bool calculating;
    // Current domain: {(x,y) : x1 <= x <= x2 and y1 <= y <= y2}
    double x1,y1,x2,y2;

    //Some helper functions
    void zoomHelper(int x, int y, double ratio);
    void recalculateHelper();
    void recalculateThread(size_t start, size_t stop);
    void abortCalculations();
public:
    explicit Fractal(Generator* gen = nullptr);
    Fractal& operator=(Fractal frac) { gen = frac.gen; return *this; }
    ~Fractal();

    // This method should be called always when there is a need for the fractal to be recalculated
    void recalculateTexture();

    // Getters:

    // Returns raw pixel data in the OpenGL format
    rgb_value_type* getTexture();
    // Returns plane coords corresponding to the pixel
    [[nodiscard]] std::pair<double, double> transformPixelToCoords(size_t w, size_t h) const;
    [[nodiscard]] size_t getWidth() const { return windowWidth; }
    [[nodiscard]] size_t getHeight() const { return windowHeight; }

    // Setters:
    void setGenerator(Generator* newGen);
    void setPalette(const string& s) { currentPaletteName = s; gen->setPalette(s); recalculateTexture();}

    // API functions:

    // Zooming
    void zoomIn(int x, int y);
    void zoomOut(int x, int y);

    // Changing center of image
    void reposition(int x, int y);
    // Resizing the window
    void resize(size_t width, size_t height);
    // Resetting the fractal; currently meaningful only for NewtonFractal fractals. NOP by default
    void reset() { abortCalculations(); gen->reset(); recalculateTexture(); }

    // Changing iterations range for better coloring
    void increaseMaxIter() { gen->increaseMaxIter(); recalculateTexture();}
    void decreaseMaxIter() { gen->decreaseMaxIter(); recalculateTexture();}
    void increaseMinIter() { gen->increaseMinIter(); recalculateTexture();}
    void decreaseMinIter() { gen->decreaseMinIter(); recalculateTexture();}

    // Resizing the domain of calculations
    void expandLeft() { x1 -= (x2 - x1) * expand_ratio;  recalculateTexture(); }
    void expandRight() { x2 += (x2 - x1) * expand_ratio; recalculateTexture(); }
    void expandDown() { y1 -= (y2 - y1) * expand_ratio;  recalculateTexture(); }
    void expandUp() { y2 += (y2 - y1) * expand_ratio; recalculateTexture(); }
    void dexpandLeft() { x1 += (x2 - x1) * expand_ratio; recalculateTexture();}
    void dexpandRight() { x2 -= (x2 - x1) * expand_ratio; recalculateTexture(); }
    void dexpandDown() { y1 += (y2 - y1) * expand_ratio; recalculateTexture();}
    void dexpandUp() { y2 -= (y2 - y1) * expand_ratio; recalculateTexture(); }

};

#endif //FRACTALS_FRACTAL_H
