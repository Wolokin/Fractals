#ifndef FRACTALS_FRACTAL_H
#define FRACTALS_FRACTAL_H

#include "constants.h"
#include "generators.h"
#include <thread>

class Fractal {
    constexpr static const double zoomRatio = 0.9;
    static const int thread_count = 20;
    constexpr static const double expandRatio = 0.1;

    size_t windowWidth = 0, windowHeight = 0;

    string currentPaletteName = default_palette;
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
    Fractal& operator=(Fractal frac) { gen = frac.gen; return *this; }
    ~Fractal();

    void recalculateTexture();

    rgb_value_type* getTexture();
    size_t getWidth() { return windowWidth; }
    size_t getHeight() { return windowHeight; }
    void zoomIn(int x, int y);
    void zoomOut(int x, int y);
    void reposition(int x, int y);
    void resize(size_t width, size_t height);
    void reset() { gen->reset(); recalculateTexture(); }
    void setGenerator(Generator* gen);
    void setPalette(const string& s) { currentPaletteName = s; gen->setPalette(s); recalculateTexture();}

    void increaseMaxIter() { gen->increaseMaxIter(); recalculateTexture();}
    void decreaseMaxIter() { gen->decreaseMaxIter(); recalculateTexture();}
    void increaseMinIter() { gen->increaseMinIter(); recalculateTexture();}
    void decreaseMinIter() { gen->decreaseMinIter(); recalculateTexture();}

    void expandWidth() { x1 -= (x2-x1)*expandRatio; x2 += (x2-x1)*expandRatio; recalculateTexture();}
    void expandHeight() { y1 -= (y2-y1)*expandRatio; y2 += (y2-y1)*expandRatio; recalculateTexture();}
    void dexpandWidth() { x1 += (x2-x1)*expandRatio; x2 -= (x2-x1)*expandRatio; recalculateTexture();}
    void dexpandHeight() { y1 += (y2-y1)*expandRatio; y2 -= (y2-y1)*expandRatio; recalculateTexture();}

    std::pair<double, double> transformPixelToCoords(size_t w, size_t h);

//    void nextPalette() { gen->nextPalette(); }
//    void previousPalette() { gen->previousPalette(); }

    void abortCalculations();

    static const map<string, Generator*> fractals;
};

#endif //FRACTALS_FRACTAL_H
