#include "MainWindow.hpp"

#include "Authenticator.hpp"
#include "ui_MainWindow.h"

#include <QGridLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(qAppName());

    createMenuBar();

    createLoginWidget();

    connect(&m_auth, &Authenticator::authenticationFinished, this,
            &MainWindow::retrievePersonalInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::quit()
{
    QApplication::quit();
}

void MainWindow::aboutClicked()
{
    QMessageBox::information(
        this, "About",
        QString("Version %1").arg(QApplication::applicationVersion()));
}

void MainWindow::retrievePersonalInfo(const QString token)
{
    m_req.setToken(token);
    m_req.requestGuilds();
}

void MainWindow::createMenuBar()
{
    m_file.setTitle("File");
    m_quit.setText("Quit");
    m_quit.setShortcut(QKeySequence::Quit);
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
    const auto l = qobject_cast<QGridLayout *>(centralWidget()->layout());
    m_login.setText("Sign in...");
    l->addWidget(&m_login);

    connect(&m_login, &QPushButton::clicked, &m_auth,
            &Authenticator::requestLogin);
}
