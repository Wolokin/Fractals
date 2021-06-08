#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "src/OpenGL/oglwidget.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // connection between fractals drop-down list and openGLWidget for fractal switching
    connect(ui->comboBox_f, SIGNAL(currentTextChanged(QString)), ui->openGLWidget, SLOT(changeFractal(QString)));
    // connection for palette switching
    connect(ui->comboBox_p, SIGNAL(currentTextChanged(QString)), ui->openGLWidget, SLOT(changePalette(QString)));
    // connection for mouse position tracking
    connect(ui->openGLWidget, SIGNAL(mouseMoved(std::string)), ui->pos_label, SLOT(mouseMoved(std::string)));
}

MainWindow::~MainWindow() {
    delete ui;
}
