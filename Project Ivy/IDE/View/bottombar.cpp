#include "bottombar.h"
#include <QHBoxLayout>
#include <QWidget>
#include <QDebug>
#include <iostream>
#include <string>
#include <sstream>

BottomBar::BottomBar(QWidget *parent) :
    QTabWidget(parent)
{
    //console
    textArea = new QTextEdit();
    this->addTab(textArea, "Console");

    //errorlist
    errorList = new QListWidget();
    this->addTab(errorList, "Errors");

    //tabwidget
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, "#323232");
    setAutoFillBackground(true);
    setPalette(Pal);

    setFixedHeight(200);
    setStyleSheet("QTextEdit, QListWidget { color: white; background-color: #2D2D2F; border-style: solid; border-width: 1px; border-color: black; } QTabWidget::pane { background-color: #2D2D2F; } QTabBar::tab { color: white; background-color: #2D2D2F; border-style: solid; border-width: 1px; border-color: black; padding: 3px;} QTabBar::tab:selected { background-color: black; }");

    errorList->addItem(new ErrorListItem(2, "First item", errorList));
    errorList->addItem(new ErrorListItem(4, "Second item", errorList));

    connect(errorList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(errorListItemDoubleClicked(QListWidgetItem*)));
}

void BottomBar::errorListItemDoubleClicked(QListWidgetItem* listItem)
{
    ErrorListItem* errorListItem = (ErrorListItem*)listItem;
}

/* Template code for overriding cout
void BottomBar::readText()
{
    std::stringstream redirectStream;
    std::cout.rdbuf(redirectStream.rdbuf());

    std::string str;
    while(std::getline(redirectStream, str))
    {
        textArea->append("/n");
        textArea->append(QString::fromStdString(str));
    }

    std::cout << "blablabla";
}*/
