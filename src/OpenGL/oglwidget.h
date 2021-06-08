#ifndef OGLWIDGET_H
#define OGLWIDGET_H


#include <QWidget>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <GL/glu.h>
#include <GL/gl.h>
#include <thread>
#include "src/Logic/constants.h"
#include "src/Logic/fractal.h"
#include "src/Logic/generators.h"
#include <string>
#include <map>
#include "fractalsSupplier.h"

class OGLWidget : public QOpenGLWidget
{
    Q_OBJECT

    QTimer *aTimer;
    FractalsSupplier fractals;

public:
    explicit OGLWidget(QWidget *parent = nullptr);
    unique_ptr<Fractal> fractal;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent* e) override;
    void wheelEvent(QWheelEvent* e) override;
    void keyPressEvent(QKeyEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
public slots:
    void changeFractal(const QString& name);
    void changePalette(const QString& name) const;
signals:
    void mouseMoved(std::string);
};

#endif // OGLWIDGET_H
