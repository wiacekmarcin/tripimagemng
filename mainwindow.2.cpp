#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "picture_simple.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PictureSimple p("../1002.jpg");
    p.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
