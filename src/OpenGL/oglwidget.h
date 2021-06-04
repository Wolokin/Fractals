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

class OGLWidget : public QOpenGLWidget
{
    Q_OBJECT

    QTimer *aTimer;
    const static size_t refreshTime = 30;


public:
    explicit OGLWidget(QWidget *parent = nullptr);
    ~OGLWidget() override;
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
    void changeFractal(QString name);
    void changePalette(QString name);
    //void recalculate();
    //std::thread calculationThread;
signals:
    void mouseMoved(std::string);
};

#endif // OGLWIDGET_H
