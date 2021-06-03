#include "myglwidget.h"
#include "ui_myglwidget.h"
#include <GL/gl.h>
#include "constants.h"
#include "fractal.h"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
    fractal = make_unique<Fractal>(new Mandelbrot, -2.5,-2.5, 2.5,2.5);
    //m_context = new QOpenGLContext(this);
}


void MyGLWidget::initializeGL()
{
    //m_context->makeCurrent();
    //makeCurrent();
    initializeOpenGLFunctions();
}


void MyGLWidget::resizeGL(int w, int h)
{
    //m_projection.setToIdentity();
   // m_projection.perspective(60.0f, w / float(h), 0.01f, 1000.0f);
}


void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D (
                GL_TEXTURE_2D,
                0,
                GL_RGB,
                defWindowWidth,
                defWindowHeight,
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
}

