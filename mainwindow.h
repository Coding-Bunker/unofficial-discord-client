#pragma once

#include <QMainWindow>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  private slots:
    void aboutClicked();

  private:
    Ui::MainWindow *ui;

    QMenu m_help;
    QAction m_about;

    void createMenuBar();
};
