#include <GL/glut.h>
#include <iostream>
#include "constants.h"
#include "fractal.h"
#include "generators.h"
#include <thread>

using namespace std;

unique_ptr<Fractal> fractal;
thread calculationThread;

void cleanup() {
    if(calculationThread.joinable()) calculationThread.join();
}

void recalculateWrapper() {
    fractal->abortCalculations();
    if(calculationThread.joinable()) {
        calculationThread.join();
    }
    calculationThread = thread([](){fractal->recalculateTexture();});
}

// https://stackoverflow.com/questions/503816/what-is-the-fastest-way-to-draw-a-2d-array-of-color-triplets-on-screen/504440#504440
void renderScene() {
    glEnable (GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D (
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            windowWidth,
            windowHeight,
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
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    cout << button << " " << state << " " << x << " " << y << endl;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        fractal->reposition(x,y);
        recalculateWrapper();
    }
    else if(button == 3 && state == GLUT_DOWN) {
        fractal->zoomIn(x,y);
        recalculateWrapper();
    }
    else if(button == 4 && state == GLUT_DOWN) {
        fractal->zoomOut(x,y);
        recalculateWrapper();
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
            fractal->increaseMaxIter();
            break;
        case '-':
            fractal->decreaseMaxIter();
            break;
        case 'c':
            fractal->nextPalette();
            break;
        case 'v':
            fractal->previousPalette();
            break;
        default:
            return;
    }
    recalculateWrapper();
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000.0/60.0, timer, 0);
}

int main(int argc, char **argv) {
    atexit(cleanup);

    fractal = make_unique<Fractal>(new Mandelbrot, -2.5,-2.5, 2.5,2.5);
    fractal->recalculateTexture();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowXPos, windowYPos);
    glutCreateWindow("Fractals!");
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(renderScene);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
