#include "buttoncontroller.h"
#include <qdebug.h>

ButtonController::ButtonController()
{
}

void ButtonController::runButtonClicked()
{
    qDebug() << "Camge into the 'runButtonClicked()' in the buttoncontroller";
    startRunning();
}

void ButtonController::buildButtonClicked()
{
    qDebug() << "Camge into the 'buildButtonClicked()' in the buttoncontroller";
    startTokenizing();
    startCompiling();
}
