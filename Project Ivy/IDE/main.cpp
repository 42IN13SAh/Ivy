#include "mainwindow.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	qRegisterMetaType<QList<QString>>("QList<QString>");

    MainWindow window;
    window.showMaximized();
    return app.exec();
}
