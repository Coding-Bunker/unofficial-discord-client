#include "mainwindow.h"

#include "./ui_mainwindow.h"

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(qAppName());

    createMenuBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::aboutClicked()
{
    qDebug() << "Prova";
}

void MainWindow::createMenuBar()
{
    m_help.setTitle("Help");
    m_about.setText("About...");
    connect(&m_about, &QAction::triggered, this, &MainWindow::aboutClicked);
    m_help.addAction(&m_about);
    ui->menubar->addMenu(&m_help);
}
