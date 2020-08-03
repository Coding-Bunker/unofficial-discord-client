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

  private:
    Ui::MainWindow *ui;

    QMenu m_aboutMenu;
};
