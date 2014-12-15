#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

class MainWindow;
class Tokenizer;
class Compiler;
class VirtualMachine;

class BaseController
{
public:
    BaseController(MainWindow *source);
	virtual ~BaseController();
protected:
	bool startBuilding(bool onlyBuild);
    void startRunning();

	MainWindow *source; //TODO: find better name?

private:
	Tokenizer *tokenizer;
	Compiler *compiler;
	VirtualMachine *virtualMachine;
};

#endif // BASECONTROLLER_H
