#include <QLibrary>
#include <future>
#include <qapplication.h>

#include "keyinputcontroller.h"
#include "mainwindow.h"
#include "codeeditor.h"

KeyInputController::KeyInputController(MainWindow *mainWindow) : BaseController(mainWindow)
{
}

KeyInputController::~KeyInputController()
{

}

/**
 *  Supproted Keystrokes:
 *      - F6 -			Start tokenizing & compiling
 *      - F5 -			Start tokenizing, compiling and running
 *
 *  @brief KeyInputController::handleKeyPressEvent Handles all key-presses that have non-default behaviour
 *	@param event The caught key event
 *	@param mainWindow A pointer to the mainWindow that should be given if that is the target for the event if it is a default key
 *	@param editor A pointer to the (text)editor area that should be given if that is the target for the event if it is a default key
 */

void KeyInputController::handleKeyPressEvent(QKeyEvent *event, MainWindow *mainWindow, CodeEditor *editor){
    switch(event->key()){
    case Qt::Key_F6:
		std::async(std::launch::async, [&]() {
			startBuilding(true, true);
		});
		break;
	case Qt::Key_F5:
		std::async(std::launch::async, [&]() {
			startRunning();
		});
		break;
	default:
		defaultEventOccured(event, mainWindow, editor);
		break;
	}
}

void KeyInputController::defaultEventOccured(QKeyEvent* event, MainWindow *mainWindow, CodeEditor *editor){
	//No shortcut(s) found; pass the event to the right class to continue default behaviour.
	//First, check if mainWindow exists and editor doesn't (since we only expect one parameter
	if (mainWindow != nullptr && editor == nullptr){
		mainWindow->defaultKeyPressEvent(event);
	}//Not the case, check if editor is not null but mainWindow is
	else if (mainWindow == nullptr && editor != nullptr){
		editor->defaultKeyPressEvent(event);
	}
	//Neither case was applicable: either they were both given or both were none. 
	//In either way, we don't know which widget to send the event to, so do nothing
}
