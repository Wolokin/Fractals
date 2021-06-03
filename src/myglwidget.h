#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "fractal.h"

namespace Ui {
class MyGLWidget;
}

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    MyGLWidget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
//    QOpenGLContext *m_context;
//    QSurface *m_surf;
private:
    unique_ptr<Fractal> fractal;
};




#endif // MYGLWIDGET_H
