#include "buttoncontroller.h"
#include <qdebug.h>

ButtonController::ButtonController(MainWindow * source) : BaseController(source)
{
}

void ButtonController::runButtonClicked()
{
    startRunning();
}

void ButtonController::buildButtonClicked()
{
    startBuilding(true, true);
}
