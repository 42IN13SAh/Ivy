#include <QDebug>
#include <QLibrary>

#include "keyinputcontroller.h"
#include "mainwindow.h"

KeyInputController::KeyInputController(MainWindow *source) : BaseController(source)
{

}

/**
 *  Supproted Keystrokes:
 *      - F6 - Start tokenizing & compiling
 *      -
 *
 *  @brief KeyInputController::handleKeyPressEvent Handles all key-presses that have non-default behaviour
 * @param event The caught key event
 */
void KeyInputController::handleKeyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_F6:
		startBuilding();
    default:
        //No shortcut(s) found; pass the event to the base class to continue default behaviour
        source->defaultKeyPressEvent(event);
    }
}
