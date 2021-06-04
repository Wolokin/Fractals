#ifndef LABEL_SIZE_H
#define LABEL_SIZE_H

#include <QLabel>
#include <string>
#include <QMouseEvent>

class label_size : public QLabel
{
    Q_OBJECT
public:
    explicit label_size(QWidget *parent = nullptr);
private slots:
    void mouseMoved(std::string);
};

#endif // LABEL_SIZE_H
