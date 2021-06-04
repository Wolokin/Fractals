#include "combobox_fractals.h"
#include <iostream>

comboBox_fractals::comboBox_fractals(QWidget *parent) : QComboBox(parent)
{
    for(auto it : Fractal::fractals) {
        addItem(QString::fromStdString(it.first));
    }
    setCurrentText(QString::fromStdString(default_fractal));
}
