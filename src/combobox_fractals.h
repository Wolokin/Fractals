#ifndef COMBOBOX_FRACTALS_H
#define COMBOBOX_FRACTALS_H

#include <QComboBox>

class comboBox_fractals : public QComboBox
{
    Q_OBJECT
public:
    explicit comboBox_fractals(QWidget *parent = nullptr);
private slots:
    void textChanged(const QString &text);

};

#endif // COMBOBOX_FRACTALS_H
