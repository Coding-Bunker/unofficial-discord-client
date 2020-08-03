#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("unofficial-discord-client");
    a.setOrganizationName("Coding Bunker");
    MainWindow w;
    w.show();
    return a.exec();
}
