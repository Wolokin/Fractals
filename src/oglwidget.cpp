#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    fractal = make_unique<Fractal>(new Mandelbrot);
    QTimer *aTimer = new QTimer;
    connect(aTimer,SIGNAL(timeout()),SLOT(repaint()));
    aTimer->start(30);
    //setMouseTracking(true);
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::initializeGL()
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::paintGL()
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D (
                GL_TEXTURE_2D,
                0,
                GL_RGB,
                fractal->getWidth(),
                fractal->getHeight(),
                0,
                GL_RGB,
                GL_FLOAT,
                fractal->getTexture()
        );

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0, -1.0);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0, -1.0);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0,  1.0);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0,  1.0);
        glEnd();

        glFlush();

//    glBegin(GL_TRIANGLES);
//        glColor3f(1.0, 0.0, 0.0);
//        glVertex3f(-0.5, -0.5, 0);
//        glColor3f(0.0, 1.0, 0.0);
//        glVertex3f( 0.5, -0.5, 0);
//        glColor3f(0.0, 0.0, 1.0);
//        glVertex3f( 0.0,  0.5, 0);
//    glEnd();
}

void OGLWidget::resizeGL(int w, int h)
{
    fractal->resize(w,h);
//    glViewport(0,0,w,h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45, (float)w/h, 0.01, 100.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(0,0,5,0,0,0,0,1,0);
}

// void OGLWidget::recalculate() {
//     fractal->abortCalculations();
//     if(calculationThread.joinable()) {
//         calculationThread.join();
//     }
//     calculationThread = std::thread([this]{fractal->recalculateTexture();});
// }

void OGLWidget::mousePressEvent(QMouseEvent* e) {
    //std::cout << e->localPos().x() << " " << e->localPos().y() << endl;
    fractal->reposition(e->localPos().x(), e->localPos().y());
}

void OGLWidget::wheelEvent(QWheelEvent* e) {
    cout << "wheel" << endl;
    if(e->angleDelta().y() < 0) {
        fractal->zoomOut(e->pos().x(), e->pos().y());
    }
    else {
        fractal->zoomIn(e->pos().x(), e->pos().y());
    }
}

void OGLWidget::changeFractal(QString name) {
    fractal->setGenerator(fractals.at(name.toStdString()));
}

void OGLWidget::changePalette(QString name) {
    fractal->setPalette(name.toStdString());
}
