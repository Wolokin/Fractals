#include "combobox_fractals.h"

comboBox_fractals::comboBox_fractals(QWidget *parent) : QComboBox(parent) {
    FractalsSupplier fractalsSupplier;
    for (const auto &it : fractalsSupplier.fractals) {
        addItem(QString::fromStdString(it.first));
    }
    setCurrentText(QString::fromStdString(default_fractal));
}
