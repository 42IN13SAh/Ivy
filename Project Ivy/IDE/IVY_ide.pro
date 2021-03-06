QT += widgets

HEADERS     = View/mainwindow.h \
              View/codeeditor.h \
              View/syntaxhighlighter.h \
    Controller/keyinputcontroller.h \
    View/buttonbar.h \
    Controller/basecontroller.h \
    Controller/buttoncontroller.h \
    View/bottombar.h \
    View/errorlistitem.h

SOURCES     = View/mainwindow.cpp \
              main.cpp \
              View/codeeditor.cpp \
              View/syntaxhighlighter.cpp \
    Controller/keyinputcontroller.cpp \
    View/buttonbar.cpp \
    Controller/basecontroller.cpp \
    Controller/buttoncontroller.cpp \
    View/bottombar.cpp \
    View/errorlistitem.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/codeeditor
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/richtext/syntaxhighlighter
INSTALLS += target

INCLUDEPATH += View/
INCLUDEPATH += Controller/
RESOURCES += \
    Resources.qrc

win32:INCLUDEPATH += "C:\Users\niek\Documents\DeveloperTwo\Ivy\Project Ivy\Ivy"
win32:LIBS += "C:\Users\niek\Documents\DeveloperTwo\Ivy\Project Ivy\Release"

win32:INCLUDEPATH += "C:\boost_1_57_0"
win32:LIBS += "C:\boost_1_57_0\stage\lib"
