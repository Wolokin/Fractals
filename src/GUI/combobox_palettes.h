#ifndef COMBOBOX_PALETTES_H
#define COMBOBOX_PALETTES_H

#include <QComboBox>
#include <iostream>
#include "palettes.h"

class comboBox_palettes : public QComboBox
{
    Q_OBJECT
public:
    explicit comboBox_palettes(QWidget *parent = nullptr);
private slots:
    void textChanged(const QString &text);
};

#endif // COMBOBOX_PALETTES_H
