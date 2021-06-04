#include "combobox_palettes.h"

comboBox_palettes::comboBox_palettes(QWidget *parent) : QComboBox(parent) {
    for(const auto& it : palettes) {
        addItem(QString::fromStdString(it.first));
    }
    setCurrentText(QString::fromStdString(default_palette));
}