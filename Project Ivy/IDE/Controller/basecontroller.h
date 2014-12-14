#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H
#include <string>
#include "qstring.h"

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
	void saveCurrentFile(MainWindow *mainWindow);
	virtual void saveFile(std::string *filePath);

	MainWindow *mainWindow;
	std::string currentFilePath;

private:
	Tokenizer *tokenizer;
	Compiler *compiler;
	VirtualMachine *virtualMachine;

	QString makeDefaultIvyFolder();
};

#endif // BASECONTROLLER_H
