#ifndef FRACTALS_DISPLAYER_H
#define FRACTALS_DISPLAYER_H

#include "constants.h"
#include "generators.h"
#include <thread>

class Fractal {
    constexpr static const double zoomRatio = 0.9;
    static const int thread_count = 20;

    size_t windowWidth, windowHeight;

    Generator* gen;
    vector<rgb_value_type> texture;
    std::thread calculationThread;
    double x1,y1,x2,y2;

    void zoomHelper(int x, int y, double ratio);
    void recalculateHelper();
    void recalculateThread(size_t start, size_t stop);

    bool calculating = false;

public:
    explicit Fractal(Generator* gen = nullptr);
    Fractal& operator=(Fractal frac) { gen = move(frac.gen); return *this; }
    ~Fractal();

    void recalculateTexture();

    rgb_value_type* getTexture() { return texture.data();}
    size_t getWidth() { return windowWidth; }
    size_t getHeight() { return windowHeight; }
    void zoomIn(int x, int y);
    void zoomOut(int x, int y);
    void reposition(int x, int y);
    void resize(size_t width, size_t height);
    void setGenerator(Generator* gen);
    void setPalette(string s) { gen->setPalette(s); recalculateTexture();}

    void increaseMaxIter() { gen->increaseMaxIter(); }
    void decreaseMaxIter() { gen->decreaseMaxIter(); }

    void nextPalette() { gen->nextPalette(); }
    void previousPalette() { gen->previousPalette(); }

    void abortCalculations() { calculating = false; };
};

#endif //FRACTALS_DISPLAYER_H
