#include "mainwindow.h"
#include <time.h>
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    QApplication app(argc, argv);
	qRegisterMetaType<QList<QString>>("QList<QString>");

    MainWindow window;
    window.showMaximized();
    return app.exec();
}
