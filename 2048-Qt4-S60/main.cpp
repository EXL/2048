#include "mainwindow.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    Qt::WindowFlags flags;
    flags |= Qt::WindowSoftkeysVisibleHint;
    flags &= ~Qt::WindowSoftkeysRespondHint;

    mainWindow.setWindowFlags(flags);
    mainWindow.showFullScreen();

    return app.exec();
}
