#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent)
        : QOpenGLWidget(parent) {
    fractal = make_unique<Fractal>(fractals.fractals.at("Mandelbrot"));
    aTimer = new QTimer;
    connect(aTimer, SIGNAL(timeout()), SLOT(repaint()));
    aTimer->start(refresh_time);
    setMouseTracking(false);
}

void OGLWidget::initializeGL() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::paintGL() {
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(
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
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0, -1.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0, -1.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.0, 1.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.0, 1.0);
    glEnd();

    glFlush();
}

void OGLWidget::resizeGL(int w, int h) {
    aTimer->stop();
    fractal->resize(w, h);
    aTimer->start();
}

void OGLWidget::mousePressEvent(QMouseEvent *e) {
    switch (e->button()) {
        case Qt::MouseButton::LeftButton:
            fractal->zoomIn(e->pos().x(), e->pos().y());
            break;
        case Qt::MouseButton::RightButton:
            fractal->zoomOut(e->pos().x(), e->pos().y());
            break;
        case Qt::MouseButton::MiddleButton:
            fractal->reposition(e->localPos().x(), e->localPos().y());
            break;
        default:
            return;
    }
    e->accept();
}

void OGLWidget::wheelEvent(QWheelEvent *e) {
    if (e->angleDelta().y() < 0) {
        fractal->zoomOut(e->pos().x(), e->pos().y());
    } else {
        fractal->zoomIn(e->pos().x(), e->pos().y());
    }
    e->accept();
}

void OGLWidget::changeFractal(const QString &name) {
    fractal->setGenerator(fractals.fractals.at(name.toStdString()));
}

void OGLWidget::changePalette(const QString &name) const {
    fractal->setPalette(name.toStdString());
}

void OGLWidget::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        case Qt::Key::Key_Plus:
            fractal->increaseMaxIter();
            break;
        case Qt::Key::Key_Minus:
            fractal->decreaseMaxIter();
            break;
        case Qt::Key::Key_BracketLeft:
            fractal->decreaseMinIter();
            break;
        case Qt::Key::Key_BracketRight:
            fractal->increaseMinIter();
            break;
        case Qt::Key::Key_Up:
            if (e->modifiers() & Qt::ControlModifier) fractal->expandUp();
            else fractal->dexpandUp();
            break;
        case Qt::Key::Key_Down:
            if (e->modifiers() & Qt::ControlModifier) fractal->expandDown();
            else fractal->dexpandDown();
            break;
        case Qt::Key::Key_Right:
            if (e->modifiers() & Qt::ControlModifier) fractal->expandRight();
            else fractal->dexpandRight();
            break;
        case Qt::Key::Key_Left:
            if (e->modifiers() & Qt::ControlModifier) fractal->expandLeft();
            else fractal->dexpandLeft();
            break;
        case Qt::Key::Key_R:
            fractal->reset();
            break;

    }
    e->accept();
}

void OGLWidget::mouseMoveEvent(QMouseEvent *e) {
    auto[x, y] = fractal->transformPixelToCoords(e->pos().x(), e->pos().y());
    std::stringstream ss;
    ss << std::fixed << std::setprecision(15) << "x: " << x << "\ny: " << y;
    mouseMoved(ss.str());
}
