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
	void startBuilding(bool onlyBuild);

protected:
    void startRunning();

	MainWindow *source; //TODO: find better name?

private:
	Tokenizer *tokenizer;
	Compiler *compiler;
	VirtualMachine *virtualMachine;
};

#endif // BASECONTROLLER_H
