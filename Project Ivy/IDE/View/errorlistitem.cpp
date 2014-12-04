#include "errorlistitem.h"
#include <QListWidgetItem>

ErrorListItem::ErrorListItem(int lineNumber, int linePosition, QString text, QListWidget *parent) :
    QListWidgetItem(text, parent)
{
    this->lineNumber = lineNumber;
	this->linePosition = linePosition;
}

int ErrorListItem::getLineNumber()
{
	return this->lineNumber;
}

int ErrorListItem::getLinePosition()
{
	return this->linePosition;
}