#include "mainwindow.h"

#include "./ui_mainwindow.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(qAppName());

    createMenuBar();

    createLoginWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::quit()
{
    qDebug() << "I'm quitting...";
    QApplication::quit();
}

void MainWindow::aboutClicked()
{
    QMessageBox::information(
        this, "About",
        QString("Version %1").arg(QApplication::applicationVersion()));
}

void MainWindow::requestLogin()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindow::createMenuBar()
{
    m_file.setTitle("File");
    m_quit.setText("Quit");
    connect(&m_quit, &QAction::triggered, this, &MainWindow::quit);
    m_file.addAction(&m_quit);

    m_help.setTitle("Help");
    m_about.setText("About...");
    connect(&m_about, &QAction::triggered, this, &MainWindow::aboutClicked);
    m_help.addAction(&m_about);

    ui->menubar->addMenu(&m_file);
    ui->menubar->addMenu(&m_help);
}

void MainWindow::createLoginWidget()
{
    centralWidget()->setLayout(new QGridLayout);
    auto l = qobject_cast<QGridLayout *>(centralWidget()->layout());
    m_email.setText("Email:");
    m_password.setText("Password:");
    m_login.setText("Sign in...");
    l->addWidget(&m_email);
    l->addWidget(&m_emailLe, 0, 1);
    l->addWidget(&m_password);
    l->addWidget(&m_passwordLe, 1, 1);
    l->addWidget(&m_login, 2, 0, 1, 2);

    connect(&m_login, &QPushButton::clicked, this, &MainWindow::requestLogin);
}
