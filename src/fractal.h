#ifndef FRACTALS_FRACTAL_H
#define FRACTALS_FRACTAL_H

#include "constants.h"
#include "generators.h"

class Fractal {
    constexpr static const double zoomRatio = 0.9;
    static const int thread_count = 20;

    size_t windowWidth, windowHeight;

    unique_ptr<Generator> gen;
    vector<rgb_value_type> texture;
    double x1,y1,x2,y2;

    void zoomHelper(int x, int y, double ratio);
    void recalculateHelper();
    void recalculateThread(size_t start, size_t stop);

    bool calculating = false;

public:
    explicit Fractal(Generator* gen = nullptr, double x1 = 0, double y1 = 0, double x2 = defWindowWidth, double y2 = defWindowHeight, size_t windowHeight = defWindowHeight, size_t windowWidth = defWindowWidth);
    Fractal& operator=(Fractal frac) { gen = move(frac.gen); return *this; }

    void recalculateTexture();

    rgb_value_type* getTexture() { return texture.data();}
    size_t getWidth() { return windowWidth; }
    size_t getHeight() { return windowHeight; }
    void zoomIn(int x, int y);
    void zoomOut(int x, int y);
    void reposition(int x, int y);
    void resize(size_t width, size_t height);

    void increaseMaxIter() { gen->increaseMaxIter(); }
    void decreaseMaxIter() { gen->decreaseMaxIter(); }

    void nextPalette() { gen->nextPalette(); }
    void previousPalette() { gen->previousPalette(); }

    void abortCalculations() { calculating = false; };
};

#endif //FRACTALS_FRACTAL_H
