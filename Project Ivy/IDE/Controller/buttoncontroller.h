#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H


#include "basecontroller.h"

class ButtonController : public BaseController
{
public:
    ButtonController();
    void runButtonClicked();
    void buildButtonClicked();
};

#endif // BUTTONCONTROLLER_H
