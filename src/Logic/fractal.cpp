#include "fractal.h"
#include <ctime>


Fractal::Fractal(Generator *gen) {
    setGenerator(gen);
}

Fractal::~Fractal() {
    abortCalculations();
}

void Fractal::recalculateThread(size_t start, size_t stop) {
    for (size_t i = start; i < stop; ++i) {
        if (not calculating) return;
        for (size_t j = 0; j < windowWidth; ++j) {
            auto[x, y] = transformPixelToCoords(j, i);
            rgb c = gen->getColor(x, y);
            for (size_t k = 0; k < pixel_data_len; ++k) {
                // OpenGL uses a different ordering, hence the reindexing
                texture[(windowHeight - i - 1) * (windowWidth * pixel_data_len) + j * pixel_data_len + k] = c[k];
            }
        }
    }
}

void Fractal::recalculateHelper() {
    thread threads[thread_count];
    calculating = true;
    for (size_t i = 0; i < thread_count; ++i) {
        threads[i] = std::thread([this, i]() {
            recalculateThread(i * windowHeight / thread_count, (i + 1) * windowHeight / thread_count);
        });
    }
    for (auto &thread : threads) {
        thread.join();
    }
    calculating = false;
}

void Fractal::recalculateTexture() {
    abortCalculations();
    calculationThread = std::thread([this] { recalculateHelper(); });
}

void Fractal::zoomIn(int x, int y) {
    zoomHelper(x, y, zoom_ratio);
}

void Fractal::zoomOut(int x, int y) {
    zoomHelper(x, y, 1 / zoom_ratio);
}

void Fractal::zoomHelper(int x, int y, double ratio) {
    double centerX = (x1 + x2) / 2;
    double centerY = (y1 + y2) / 2;
    double newSizeX = (x2 - x1) * ratio / 2;
    double newSizeY = (y2 - y1) * ratio / 2;
    double newCenterX = (x1 + (x2 - x1) * x / windowWidth + centerX) / 2;
    double newCenterY = (y1 + (y2 - y1) * y / windowHeight + centerY) / 2;
    x2 = newCenterX + newSizeX;
    x1 = newCenterX - newSizeX;
    y2 = newCenterY + newSizeY;
    y1 = newCenterY - newSizeY;
    recalculateTexture();
}

void Fractal::resize(size_t width, size_t height) {
    abortCalculations();
    windowWidth = width;
    windowHeight = height;
    texture.reserve(windowWidth * windowHeight * pixel_data_len);
    recalculateTexture();
}

void Fractal::reposition(int x, int y) {
    zoomHelper(x, y, 1);
}

void Fractal::setGenerator(Generator *newGen) {
    this->gen = newGen;
    newGen->resetIntervals(x1, x2, y1, y2);
    newGen->setPalette(currentPaletteName);
    recalculateTexture();
}

void Fractal::abortCalculations() {
    calculating = false;
    if (calculationThread.joinable()) {
        calculationThread.join();
    }
}

std::pair<double, double> Fractal::transformPixelToCoords(size_t w, size_t h) const {
    return std::pair(x1 + ((x2 - x1) * w) / windowWidth, y1 + ((y2 - y1) * h) / windowHeight);
}

rgb_value_type *Fractal::getTexture() {
    if (gen->needsUpdate() && not calculating) {
        recalculateTexture();
        gen->updateDone();
    }
    return texture.data();
}


