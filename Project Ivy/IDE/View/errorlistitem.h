#ifndef ERRORLISTITEM_H
#define ERRORLISTITEM_H

#include <QListWidgetItem>
#include <QListWidget>

class ErrorListItem : public QListWidgetItem
{
public:
    explicit ErrorListItem(int lineNumber, QString text, QListWidget *parent = 0);
    int lineNumber;

};

#endif // ERRORLISTITEM_H
