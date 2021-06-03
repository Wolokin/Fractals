#include "combobox_palettes.h"

comboBox_palettes::comboBox_palettes(QWidget *parent) : QComboBox(parent) {
    for(auto it : palettes) {
        addItem(QString::fromStdString(it.first));
    }
    setEditText("inferno");
}

void comboBox_palettes::textChanged(const QString &text) {
    std::cout << text.toStdString() << std::endl;
    //ui->
}