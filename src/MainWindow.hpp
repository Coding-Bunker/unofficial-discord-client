#pragma once

#include "Authenticator.hpp"
#include "Requester.hpp"

#include <QMainWindow>
#include <QMenu>
#include <QPushButton>

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
    void retrievePersonalInfo(const QString token);

  private:
    Ui::MainWindow *ui;

    QMenu m_help;
    QMenu m_file;
    QAction m_about;
    QAction m_quit;

    QPushButton m_login;

    Authenticator m_auth;
    Requester m_req;

    void createMenuBar();
    void createLoginWidget();
};
