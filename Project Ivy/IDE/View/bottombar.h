#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QTabWidget>
#include <QTextEdit>
#include <QListWidget>
#include <vector>
#include "errorlistitem.h"

class BottomBar : public QTabWidget
{
    Q_OBJECT
public:
    explicit BottomBar(QWidget *parent = 0);

signals:

public slots:
    void errorListItemDoubleClicked(QListWidgetItem* listItem);

private:
    QTextEdit *textArea;
    QListWidget *errorList;

    void readText();
};

#endif // BOTTOMBAR_H
