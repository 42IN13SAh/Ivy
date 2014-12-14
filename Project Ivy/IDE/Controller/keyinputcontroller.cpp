#include <QDebug>
#include <QLibrary>
#include <qapplication.h>

#include "keyinputcontroller.h"
#include "mainwindow.h"

KeyInputController::KeyInputController(MainWindow *source) : BaseController(source)
{

}

/**
 *  Supproted Keystrokes:
 *      - F6 -			Start tokenizing & compiling
 *      - F5 -			Start tokenizing, compiling and running
 *		- ctrl + s -	Save the current source code to a local file
 *
 *  @brief KeyInputController::handleKeyPressEvent Handles all key-presses that have non-default behaviour
 * @param event The caught key event
 */
void KeyInputController::handleKeyPressEvent(QKeyEvent *event){
	switch (event->key()){
	case Qt::Key_F6:
		startBuilding(true);
		break;
	case Qt::Key_F5:
		startRunning();
		break;
	case Qt::Key_S:{
					   if (QApplication::keyboardModifiers() == Qt::ControlModifier){ //note for future: never use QKeyEvent::modifiers(); it's unreliable 
						   saveCurrentFile();
					   }
					   break;
	}
	default:
		//No shortcut(s) found; pass the event to the base class to continue default behaviour
		source->defaultKeyPressEvent(event);
		break;
	}
}
