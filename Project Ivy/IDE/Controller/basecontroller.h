#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <qobject.h>

class MainWindow;
class Tokenizer;
class Compiler;
class VirtualMachine;

class BaseController : public QObject
{
	Q_OBJECT

public:
    BaseController(MainWindow *source);
	virtual ~BaseController();
	bool startBuilding(bool onlyBuild, bool showConsoleOutput);
	void startRunning();

signals:
	void clearBeforeBuilding();
	void addError(int, int, QString);

protected:
	MainWindow *source;

private:
	Tokenizer *tokenizer;
	Compiler *compiler;
	VirtualMachine *virtualMachine;

};

#endif // BASECONTROLLER_H
