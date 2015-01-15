#ifndef ERRORLISTITEM_H
#define ERRORLISTITEM_H

#include <QListWidgetItem>
#include <QListWidget>

class ErrorListItem : public QListWidgetItem
{
public:
    explicit ErrorListItem(int lineNumber, int linePosition, QString text, QListWidget *parent = 0);
	virtual ~ErrorListItem();

	int getLineNumber();
	int getLinePosition();
private:
    int lineNumber;
	int linePosition;
};

#endif // ERRORLISTITEM_H
