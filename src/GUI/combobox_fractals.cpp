#include "combobox_fractals.h"
#include <iostream>

comboBox_fractals::comboBox_fractals(QWidget *parent) : QComboBox(parent)
{
    Fractals fractals;
    for(const auto& it : fractals.fractals) {
        addItem(QString::fromStdString(it.first));
    }
    setCurrentText(QString::fromStdString(default_fractal));
}
