#include "MainWindow.hpp"

#include "DiscordAPI.hpp"
#include "ui_MainWindow.h"

#include <QDesktopServices>
#include <QGridLayout>
#include <QMessageBox>
#include <QNetworkReply>
#include <QTcpServer>
#include <QUrlQuery>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(qAppName());

    createMenuBar();

    createLoginWidget();

    auto server = new QTcpServer(this);
    server->listen(QHostAddress::LocalHost, 8000);
    connect(server, &QTcpServer::newConnection, this,
            [&]() { qDebug() << "new connection on server"; });
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
    // TODO(guerra): move this part in separated class
    QUrl url(DiscordAPI::authorize);
    QUrlQuery query;
    query.addQueryItem("response_type", "code");
    query.addQueryItem("client_id", DiscordAPI::clientId);
    query.addQueryItem("scope", "identify%20email");
    query.addQueryItem("redirect_uri", "http://localhost:8000");
    url.setQuery(query);
    QDesktopServices::openUrl(url);
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
    // TODO(guerra): move this widget in separated class
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
