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
#include "constants.h"
#include "fractal.h"
#include "generators.h"

class OGLWidget : public QOpenGLWidget
{
public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent* e) override;
    void wheelEvent(QWheelEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override {cout << "move" << endl;};
private:
    void recalculate();
    unique_ptr<Fractal> fractal;
    std::thread calculationThread;
};

#endif // OGLWIDGET_H
