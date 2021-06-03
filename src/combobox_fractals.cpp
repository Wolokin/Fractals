#include "combobox_fractals.h"
#include <iostream>

comboBox_fractals::comboBox_fractals(QWidget *parent) : QComboBox(parent)
{
    for(auto it : OGLWidget::fractals) {
        addItem(QString::fromStdString(it.first));
    }

    //connect(this, SIGNAL(currentTextChanged(QString)), this, SLOT(textChanged(QString)));
}
