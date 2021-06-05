#include "label_size.h"

label_size::label_size(QWidget *parent) : QLabel(parent)
{

}

void label_size::mouseMoved(const std::string& s) {
    setText(QString::fromStdString(s));
}
