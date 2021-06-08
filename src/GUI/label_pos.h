#ifndef LABEL_SIZE_H
#define LABEL_SIZE_H

#include <QLabel>
#include <string>
#include <QMouseEvent>

class label_pos : public QLabel
{
    Q_OBJECT
public:
    explicit label_pos(QWidget *parent = nullptr) : QLabel{parent} {} ;
private slots:
    void mouseMoved(const std::string&);
};

#endif // LABEL_SIZE_H
