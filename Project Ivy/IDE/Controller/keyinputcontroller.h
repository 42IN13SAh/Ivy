#ifndef KEYINPUTCONTROLLER_H
#define KEYINPUTCONTROLLER_H
#include <QKeyEvent>

#include "basecontroller.h"
class CodeEditor;
class MainWindow;


class KeyInputController : public BaseController
{
public:
	KeyInputController(MainWindow *mainWindow);

	void handleKeyPressEvent(QKeyEvent* event, MainWindow *mainWindow, CodeEditor *editor);

private:
	void defaultEventOccured(QKeyEvent* event, MainWindow *mainWindow, CodeEditor *editor);
};

#endif // KEYINPUTCONTROLLER_H
