#include <QtGui>
#include <QApplication>

 #include "codeeditor.h"

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);

     CodeEditor editor;
     editor.setWindowTitle(QObject::tr("Ivy"));
 #if defined(Q_OS_SYMBIAN)
     editor.showMaximized();
 #else
     editor.showMaximized();
 #endif
     return app.exec();;
 }
