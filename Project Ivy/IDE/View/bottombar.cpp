#include "bottombar.h"
#include "mainwindow.h"
#include <QHBoxLayout>
#include <QWidget>
#include <iostream>
#include <string>
#include <sstream>

BottomBar::BottomBar(QWidget *parent) :
    QTabWidget(parent)
{
	this->parent = (MainWindow*)parent;

    //console
    textArea = new QTextEdit();
	textArea->setReadOnly(true);
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

    connect(errorList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(errorListItemDoubleClicked(QListWidgetItem*)));

	createRedirector();
}

void BottomBar::errorListItemDoubleClicked(QListWidgetItem* listItem)
{
    ErrorListItem* errorListItem = (ErrorListItem*)listItem;
	parent->getCodeEditor()->moveCursor(errorListItem->getLineNumber(), errorListItem->getLinePosition());
}

void BottomBar::addError(int lineNumber, int linePosition, std::string text)
{
	errorList->addItem(new ErrorListItem(lineNumber, linePosition, QString::fromStdString(text), errorList));
}

void BottomBar::clearErrorList()
{
	errorList->clear();
}

void outcallback(const char* ptr, std::streamsize count, void* textArea)
{
	(void)count;
	QTextEdit* textEdit = static_cast<QTextEdit*>(textArea);

	std::string str(ptr);

	textEdit->append(QString::fromStdString(str));
}

void BottomBar::createRedirector()
{
	stdRedirector = new StdRedirector<>(std::cout, outcallback, textArea);
}