#include "fractal.h"
#include <ctime>


Fractal::Fractal(Generator* gen) {
    setGenerator(gen);
}

Fractal::~Fractal() {
    abortCalculations();
}

long get_timestamp() {
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    return spec.tv_sec * 1000000 + spec.tv_nsec / 1000;
}

void Fractal::recalculateThread(size_t start, size_t stop) {
    long t = get_timestamp();
    for(size_t i = start; i < stop; ++i) {
        if(not calculating) return;
        for(size_t j = 0; j < windowWidth; ++j) {
            //double x = x1 + ((x2-x1) * j) / windowWidth;
            //double y = y1 + ((y2-y1) * i) / windowHeight;
            auto[x,y] = transformPixelToCoords(j,i);
            rgb c = gen->getColor(x,y);
            texture[(windowHeight - i - 1)*(windowWidth * pixel_data_len) + j * pixel_data_len + 0] = c[0];
            texture[(windowHeight - i - 1)*(windowWidth * pixel_data_len) + j * pixel_data_len + 1] = c[1];
            texture[(windowHeight - i - 1)*(windowWidth * pixel_data_len) + j * pixel_data_len + 2] = c[2];
        }
    }
    // cout << get_timestamp() - t << endl;
}

void Fractal::recalculateHelper() {
    thread threads[thread_count];
    calculating = true;
    for(size_t i = 0; i < thread_count; ++i) {
        threads[i] = std::thread([this,i](){ recalculateThread(i*windowHeight/thread_count, (i+1)*windowHeight/thread_count);});
    }
    for(auto & thread : threads) {
        thread.join();
    }
    calculating = false;
}

void Fractal::recalculateTexture() {
    abortCalculations();
    calculationThread = std::thread([this]{recalculateHelper();});
}

void Fractal::zoomIn(int x, int y) {
    zoomHelper(x,y,zoomRatio);
}

void Fractal::zoomOut(int x, int y) {
    zoomHelper(x,y,1/zoomRatio);
}

void Fractal::zoomHelper(int x, int y, double ratio) {
    double centerX = (x1+x2)/2;
    double centerY = (y1+y2)/2;
    double newSizeX = (x2-x1)*ratio/2;
    double newSizeY = (y2-y1)*ratio/2;
    double newCenterX = (x1 + (x2-x1) * x / windowWidth + centerX) / 2;
    double newCenterY = (y1 + (y2-y1) * y / windowHeight + centerY) / 2;
    x2 = newCenterX + newSizeX;
    x1 = newCenterX - newSizeX;
    y2 = newCenterY + newSizeY;
    y1 = newCenterY - newSizeY;
    recalculateTexture();
}

void Fractal::resize(size_t width, size_t height) {
//    if(windowWidth != 0 && windowHeight != 0) {
//        double w = x2 - x1;
//        double h = y2 - y1;
//        w = w * (max(1.0, (double) width / height / ((double) windowWidth / windowHeight)));
//        h = h * (max(1.0, (double) height / width / ((double) windowHeight / windowWidth)));
//        x1 -= w / 2;
//        x2 += w / 2;
//        y1 -= h / 2;
//        y2 += h / 2;
//    }
    abortCalculations();
    windowWidth = width;
    windowHeight = height;
    texture.reserve(windowWidth * windowHeight * pixel_data_len);
    recalculateTexture();
}

void Fractal::reposition(int x, int y) {
    zoomHelper(x,y,1);
}

void Fractal::setGenerator(Generator* gen) {
    this->gen = gen;
    gen->resetIntervals(x1, x2, y1, y2);
    gen->setPalette(currentPaletteName);
    recalculateTexture();
}

void Fractal::abortCalculations() {
    calculating = false;
    if(calculationThread.joinable()) {
        calculationThread.join();
    }
}

std::pair<double, double> Fractal::transformPixelToCoords(size_t w, size_t h) {
    return std::pair(x1 + ((x2-x1) * w) / windowWidth, y1 + ((y2-y1) * h) / windowHeight);
}

rgb_value_type *Fractal::getTexture() {
    if(gen->needsUpdate() && not calculating) {
        recalculateTexture();
        gen->updateDone();
    }
    return texture.data();
}


