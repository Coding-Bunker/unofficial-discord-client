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

    connect(&m_localServer, &QTcpServer::newConnection, this,
            &MainWindow::newConnectionOnLocalServer);
    m_localServer.listen(QHostAddress::LocalHost, 8000);
}

MainWindow::~MainWindow()
{
    m_localServer.close();
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

void MainWindow::newConnectionOnLocalServer()
{
    qDebug() << "new connection on server";
    auto s   = qobject_cast<QTcpServer *>(sender());
    auto sok = s->nextPendingConnection();
    if (sok != nullptr) {
        connect(sok, &QTcpSocket::readyRead, this,
                &MainWindow::readDataFromSocket);
        connect(sok, &QTcpSocket::disconnected, sok, &QTcpSocket::deleteLater);
    }
}

void MainWindow::readDataFromSocket()
{
    auto s = qobject_cast<QTcpSocket *>(sender());
    if (s == nullptr) {
        return;
    }

    auto data = s->readAll();
    auto v    = data.split('=');
    m_token   = v.at(1).left(30);
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
    auto l = qobject_cast<QGridLayout *>(centralWidget()->layout());
    m_login.setText("Sign in...");
    l->addWidget(&m_login);

    connect(&m_login, &QPushButton::clicked, this, &MainWindow::requestLogin);
}
