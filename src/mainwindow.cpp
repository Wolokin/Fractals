#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "oglwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->comboBox_f, SIGNAL(currentTextChanged(QString)), ui->openGLWidget, SLOT(changeFractal(QString)));
    connect(ui->comboBox_p, SIGNAL(currentTextChanged(QString)), ui->openGLWidget, SLOT(changePalette(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
