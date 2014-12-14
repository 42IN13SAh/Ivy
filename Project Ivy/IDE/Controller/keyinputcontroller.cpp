#include <QDebug>
#include <QLibrary>
#include <qapplication.h>

#include "keyinputcontroller.h"
#include "mainwindow.h"
#include "codeeditor.h"

KeyInputController::KeyInputController(MainWindow *mainWindow) : BaseController(mainWindow)
{
}

/**
 *  Supproted Keystrokes:
 *      - F6 -			Start tokenizing & compiling
 *      - F5 -			Start tokenizing, compiling and running
 *		- ctrl + s -	Save the current source code to a local file
 *
 *  @brief KeyInputController::handleKeyPressEvent Handles all key-presses that have non-default behaviour
 *	@param event The caught key event
 *	@param mainWindow A pointer to the mainWindow that should be given if that is the target for the event if it is a default key
 *	@param editor A pointer to the (text)editor area that should be given if that is the target for the event if it is a default key
 */
void KeyInputController::handleKeyPressEvent(QKeyEvent *event, MainWindow *mainWindow, CodeEditor *editor){
	switch (event->key()){
	case Qt::Key_F6:
		startBuilding(true);
		break;
	case Qt::Key_F5:
		startRunning();
		break;
	case Qt::Key_S:{
					   if (QApplication::keyboardModifiers() == Qt::ControlModifier){ //note for future: never use event->modifiers(); it's unreliable 
						   this->saveCurrentFile(this->mainWindow); //since parameter mainWindow can be a nullptr, and this is just for dialog placement
					   }
					   else{
						   //S was pressed, bu no control along with it: pass it as a default event
						   defaultEventOccured(event, mainWindow, editor);
					   }
					   break;
	}
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