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

void MainWindow::retrievePersonalInfo(const QString token,
                                      const QJsonObject &meInfo)
{
    m_userLogged.populate(meInfo);
    qDebug() << m_userLogged;
    m_req.setToken(token);
    connect(&m_req, &Requester::guildsFinished, this, &MainWindow::guildsReady);
    m_req.requestGuilds();
}

void MainWindow::guildsReady(const QJsonArray &array)
{
    m_userLogged.setGuilds(array);
    qDebug() << m_userLogged.guilds();
    m_guildsModel = std::make_unique<GuildsModel>(m_userLogged.guilds());
    m_guildsView.setModel(m_guildsModel.get());
    qDebug() << m_stack.count();
    m_stack.addWidget(&m_guildsView);
    m_stack.setCurrentIndex(1);
    qDebug() << m_stack.count();
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
    m_login.setText("Sign in...");

    centralWidget()->setLayout(new QGridLayout);
    const auto l = qobject_cast<QGridLayout *>(centralWidget()->layout());

    m_stack.addWidget(&m_login);
    l->addWidget(&m_stack);

    connect(&m_login, &QPushButton::clicked, &m_auth,
            &Authenticator::requestLogin);
}
