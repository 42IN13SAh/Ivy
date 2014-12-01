#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

class BaseController
{
public:
    BaseController();
protected:
    void startTokenizing();
    void startCompiling();
    void startRunning();
};

#endif // BASECONTROLLER_H
