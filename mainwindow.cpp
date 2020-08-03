#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(qAppName());

    m_aboutMenu.setTitle("About");
    ui->menubar->addMenu(&m_aboutMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}
