#ifndef KEYINPUTCONTROLLER_H
#define KEYINPUTCONTROLLER_H
#include <QKeyEvent>

#include "basecontroller.h"
class MainWindow;


class KeyInputController : public BaseController
{
public:
    KeyInputController(MainWindow *source);

    void handleKeyPressEvent(QKeyEvent* event);
};

#endif // KEYINPUTCONTROLLER_H
