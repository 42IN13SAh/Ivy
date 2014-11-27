#ifndef KEYINPUTCONTROLLER_H
#define KEYINPUTCONTROLLER_H
#include <QKeyEvent>

#include "basecontroller.h"
class MainWindow;


class KeyInputController : public BaseController
{
public:
    KeyInputController(MainWindow *window);

    void handleKeyPressEvent(QKeyEvent* event);

private:
    MainWindow *source; //TODO: find better name?
};

#endif // KEYINPUTCONTROLLER_H
