/********************************************************************************
** Form generated from reading UI file 'codeeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODEEDITOR_H
#define UI_CODEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CodeEditor
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CodeEditor)
    {
        if (CodeEditor->objectName().isEmpty())
            CodeEditor->setObjectName(QStringLiteral("CodeEditor"));
        CodeEditor->resize(400, 300);
        menuBar = new QMenuBar(CodeEditor);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CodeEditor->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CodeEditor);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CodeEditor->addToolBar(mainToolBar);
        centralWidget = new QWidget(CodeEditor);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CodeEditor->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CodeEditor);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CodeEditor->setStatusBar(statusBar);

        retranslateUi(CodeEditor);

        QMetaObject::connectSlotsByName(CodeEditor);
    } // setupUi

    void retranslateUi(QMainWindow *CodeEditor)
    {
        CodeEditor->setWindowTitle(QApplication::translate("CodeEditor", "CodeEditor", 0));
    } // retranslateUi

};

namespace Ui {
    class CodeEditor: public Ui_CodeEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODEEDITOR_H
