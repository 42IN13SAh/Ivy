#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

class MainWindow;

class BaseController
{
public:
    BaseController(MainWindow *source);
protected:
	void startBuilding();
    void startRunning();

	MainWindow *source; //TODO: find better name?
};

#endif // BASECONTROLLER_H
