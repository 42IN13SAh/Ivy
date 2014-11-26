#include "errorlistitem.h"
#include <QListWidgetItem>

ErrorListItem::ErrorListItem(int lineNumber, QString text, QListWidget *parent) :
    QListWidgetItem(text, parent)
{
    this->lineNumber = lineNumber;
}
