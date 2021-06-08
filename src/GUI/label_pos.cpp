#include "label_pos.h"

void label_pos::mouseMoved(const std::string& s) {
    setText(QString::fromStdString(s));
}
