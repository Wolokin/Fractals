#ifndef FRACTALS_FRACTAL_H
#define FRACTALS_FRACTAL_H

#include "constants.h"
#include "generators.h"

class Fractal {
    constexpr static const double zoomRatio = 0.9;
    static const int thread_count = 20;

    unique_ptr<Generator> gen;
    float texture[windowHeight][windowWidth][pixelDataLen]{};
    double x1,y1,x2,y2;

    void zoomHelper(int x, int y, double ratio);
    void recalculateHelper(size_t start, size_t stop);

    bool calculating = false;

public:
    explicit Fractal(Generator* gen = nullptr, double x1 = 0, double y1 = 0, double x2 = windowWidth, double y2 = windowHeight)
        : gen{gen}, x1{x1}, y1{y1}, x2{x2}, y2{y2} {};
    Fractal& operator=(Fractal frac) { gen = move(frac.gen); return *this; }

    void recalculateTexture();
    float* getTexture() { return &texture[0][0][0];}
    void zoomIn(int x, int y);
    void zoomOut(int x, int y);
    void reposition(int x, int y);

    void increaseMaxIter() { gen->increaseMaxIter(); }
    void decreaseMaxIter() { gen->decreaseMaxIter(); }

    void nextPalette() { gen->nextPalette(); }
    void previousPalette() { gen->previousPalette(); }

    void abortCalculations() { calculating = false; };
};

#endif //FRACTALS_FRACTAL_H
