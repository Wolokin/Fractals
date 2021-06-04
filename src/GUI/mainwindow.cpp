#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "src/OpenGL/oglwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->comboBox_f, SIGNAL(currentTextChanged(QString)), ui->openGLWidget, SLOT(changeFractal(QString)));
    connect(ui->comboBox_p, SIGNAL(currentTextChanged(QString)), ui->openGLWidget, SLOT(changePalette(QString)));
    connect(ui->openGLWidget, SIGNAL(mouseMoved(std::string)), ui->size_label, SLOT(mouseMoved(std::string)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
