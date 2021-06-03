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
#include "src/Logic/displayer.h"
#include "src/Logic/generators.h"
#include <string>
#include <map>

class OGLWidget : public QOpenGLWidget
{
    Q_OBJECT


public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();
    unique_ptr<Fractal> fractal;
    static const map<string, Generator*> fractals;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent* e) override;
    void wheelEvent(QWheelEvent* e) override;
    //void mouseMoveEvent(QMouseEvent* e) override {cout << "move" << endl;};
public slots:
    void changeFractal(QString name);
    void changePalette(QString name);
    //void recalculate();
    //std::thread calculationThread;
};

#endif // OGLWIDGET_H
