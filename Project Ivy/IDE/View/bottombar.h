#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QTabWidget>
#include <QTextEdit>
#include <QListWidget>
#include <vector>
#include "errorlistitem.h"
#include "StdRedirector.h"

class MainWindow;

class BottomBar : public QTabWidget
{
    Q_OBJECT
public:
    explicit BottomBar(QWidget *parent = 0);
	virtual ~BottomBar();
	void addError(int lineNumber, int linePosition, QString text);
	void clearErrorList();
	void clearConsole();
	std::vector<ErrorListItem*> getAllErrors();
	void showConsole();

signals:
	void stdOut(QString);

public slots:
    void errorListItemDoubleClicked(QListWidgetItem* listItem);
	void onStdOut(QString);

private:
	MainWindow *parent;

    QTextEdit *textArea;
    QListWidget *errorList;

	StdRedirector<> *stdRedirector;

	void createRedirector();
};

#endif // BOTTOMBAR_H
