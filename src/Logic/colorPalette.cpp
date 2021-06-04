//
// Created by filip on 30.05.2021.
//

#include "colorPalette.h"

#include <utility>

colorPalette::colorPalette(string name, double left, double right) : paletteName{std::move(name)}, palette{palettes.at(paletteName)},
    start{left}, end{right}, step{(end - start) / palette.size()} {}

rgb colorPalette::getColor(double x) {
    size_t left = (x - start) / (end - start) * palette.size();
    size_t right = left + 1;
    if(right >= palette.size()) {
        return palette[palette.size()-1];
    }
    rgb_value_type ls = (x - left * step) / step;
    rgb_value_type rs = (right * step - x) / step;
    if(left >= 1 && right < palette.size() - 1) {
        return rgb{
                (palette[left][0]*ls + palette[right][0]*rs)*2/3 + (palette[left-1][0]*ls + palette[right+1][0]*rs)*1/3,
                (palette[left][1]*ls + palette[right][1]*rs)*2/3 + (palette[left-1][1]*ls + palette[right+1][1]*rs)*1/3,
                (palette[left][2]*ls + palette[right][2]*rs)*2/3 + (palette[left-1][2]*ls + palette[right+1][2]*rs)*1/3,
        };
    }
    return rgb{
        palette[left][0]*ls + palette[right][0]*rs,
        palette[left][1]*ls + palette[right][1]*rs,
        palette[left][2]*ls + palette[right][2]*rs,
    };
}

void colorPalette::resize(double left, double right) {
    start = left;
    end = right;
    step = (end -start) / palette.size();
}

//void colorPalette::next() {
//    auto it = palettes.find(paletteName);
//    ++it;
//    if(it == palettes.end()) {
//        it = palettes.begin();
//    }
//    auto kv = *it;
//    paletteName = kv.first;
//    palette = kv.second;
//    resize(start,end);
//    std::cout << "Current palette: " << paletteName << endl;
//}
//
//void colorPalette::previous() {
//    auto it = palettes.find(paletteName);
//    --it;
//    if(it == palettes.begin()) {
//        it = --palettes.end() ;
//    }
//    auto kv = *it;
//    paletteName = kv.first;
//    palette = kv.second;
//    resize(start,end);
//    std::cout << "Current palette: " << paletteName << endl;
//}
