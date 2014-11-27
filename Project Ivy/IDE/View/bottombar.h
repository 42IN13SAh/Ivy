#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QTabWidget>
#include <QTextEdit>
#include <QListWidget>
#include <vector>
#include "errorlistitem.h"

class MainWindow;

class BottomBar : public QTabWidget
{
    Q_OBJECT
public:
    explicit BottomBar(QWidget *parent = 0);
	void addError(int lineNumber, int linePosition, std::string text);
	void clearErrorList();

signals:

public slots:
    void errorListItemDoubleClicked(QListWidgetItem* listItem);

private:
	MainWindow *parent;

    QTextEdit *textArea;
    QListWidget *errorList;

    void readText();
};

#endif // BOTTOMBAR_H
