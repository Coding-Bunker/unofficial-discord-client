#include "MainWindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("unofficial-discord-client");
    a.setOrganizationName("Coding Bunker");
    a.setApplicationVersion("0.0.1");
    MainWindow w;
    w.show();
    return a.exec();
}
