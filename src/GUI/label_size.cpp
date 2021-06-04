#include "label_size.h"

label_size::label_size(QWidget *parent) : QLabel(parent)
{

}

void label_size::mouseMoved(std::string s) {
    //std::string s = "x: (" + std::to_string(e->pos().x()) + "), y: (" + std::to_string(e->pos().y()) + ")";
    setText(QString::fromStdString(s));
}
