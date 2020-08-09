#include "MainWindow.hpp"

#include "DiscordAPI.hpp"
#include "ui_MainWindow.h"

#include <QDesktopServices>
#include <QGridLayout>
#include <QJsonDocument>
#include <QJsonObject>
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
    const auto s   = qobject_cast<QTcpServer *>(sender());
    const auto sok = s->nextPendingConnection();
    if (sok != nullptr) {
        connect(sok, &QTcpSocket::readyRead, this,
                &MainWindow::readDataFromSocket);
        connect(sok, &QTcpSocket::disconnected, sok, &QTcpSocket::deleteLater);
    }
}

void MainWindow::readDataFromSocket()
{
    const auto s = qobject_cast<QTcpSocket *>(sender());
    if (s == nullptr) {
        return;
    }

    const auto data = s->readAll();
    const auto v    = data.split('=');
    m_codeGrant     = v.at(1).left(30);
    requestToken();
}

void MainWindow::tokenResponse()
{
    const auto r = qobject_cast<QNetworkReply *>(sender());
    if (r == nullptr) {
        qWarning() << "error response" << Q_FUNC_INFO;
        return;
    }

    r->deleteLater();
    const auto doc = QJsonDocument::fromJson(r->readAll());
    const auto obj = doc.object();
    m_token = obj.value(DiscordAPI::DiscordTags::access_token).toString();
    m_refreshToken =
        obj.value(DiscordAPI::DiscordTags::refresh_token).toString();
    m_expireTime = obj.value(DiscordAPI::DiscordTags::expires_in).toInt();
    qDebug() << m_token << m_refreshToken << m_expireTime;
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

    connect(&m_login, &QPushButton::clicked, this, &MainWindow::requestLogin);
}

void MainWindow::requestToken()
{
    QUrl url(DiscordAPI::token);
    QUrlQuery query;
    query.addQueryItem("client_id", DiscordAPI::clientId);
    query.addQueryItem("client_secret", DiscordAPI::clientSecret);
    query.addQueryItem("grant_type", "authorization_code");
    query.addQueryItem("code", m_codeGrant);
    query.addQueryItem("redirect_uri", "http://localhost:8000");
    query.addQueryItem("scope", "identify email connections");
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader,
                  "application/x-www-form-urlencoded");
    auto reply = m_nam.post(req, query.query().toUtf8());
    connect(reply, &QNetworkReply::finished, this, &MainWindow::tokenResponse);
}
