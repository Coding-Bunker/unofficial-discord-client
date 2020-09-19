#pragma once

#include "Authenticator.hpp"
#include "GuildsModel.hpp"
#include "Requester.hpp"
#include "User.hpp"

#include <QListView>
#include <QMainWindow>
#include <QMenu>
#include <QPushButton>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
} // namespace Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  private slots:
    void quit();
    void aboutClicked();
    void retrievePersonalInfo(const QString token, const QJsonObject &meInfo);
    void guildsReady(const QJsonArray &array);

  private:
    Ui::MainWindow *ui;

    QMenu m_help;
    QMenu m_file;
    QAction m_about;
    QAction m_quit;

    QPushButton m_login;
    QStackedWidget m_stack;

    QListView m_guildsView;
    std::unique_ptr<GuildsModel> m_guildsModel;

    Authenticator m_auth;
    Requester m_req;
    User m_userLogged;

    void createMenuBar();
    void createLoginWidget();
};
