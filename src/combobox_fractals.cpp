#include "combobox_fractals.h"
#include <iostream>

comboBox_fractals::comboBox_fractals(QWidget *parent) : QComboBox(parent)
{
    addItem("Option 1");
    addItem("Option 2");
    addItem("Option 3");

    connect(this, SIGNAL(currentTextChanged(QString)), this, SLOT(textChanged(QString)));
}

void comboBox_fractals::textChanged(const QString &text) {
    std::cout << text.toStdString() << std::endl;
}
