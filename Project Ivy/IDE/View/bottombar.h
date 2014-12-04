#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QTabWidget>
#include <QTextEdit>
#include <QListWidget>
#include <vector>
#include "errorlistitem.h"
#include "../StdRedirector.h"

class MainWindow;

class BottomBar : public QTabWidget
{
    Q_OBJECT
public:
    explicit BottomBar(QWidget *parent = 0);
	void addError(int lineNumber, int linePosition, std::string text);
	void clearErrorList();
	void clearConsole();

signals:

public slots:
    void errorListItemDoubleClicked(QListWidgetItem* listItem);

private:
	MainWindow *parent;

    QTextEdit *textArea;
    QListWidget *errorList;

	StdRedirector<> *stdRedirector;

	void createRedirector();
};

#endif // BOTTOMBAR_H
