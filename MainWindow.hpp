#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QTcpServer>

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
    void requestLogin();
    void newConnectionOnLocalServer();
    void readDataFromSocket();
    void tokenResponse();

  private:
    Ui::MainWindow *ui;

    QMenu m_help;
    QMenu m_file;
    QAction m_about;
    QAction m_quit;

    QPushButton m_login;

    QNetworkAccessManager m_nam;
    QTcpServer m_localServer;
    QString m_codeGrant;
    QString m_token;
    QString m_refreshToken;
    int m_expireTime;

    void createMenuBar();
    void createLoginWidget();
    void requestToken();
};
