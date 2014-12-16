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
	void saveCurrentCodeToNewFile(MainWindow *mainWindow); //Two public functions since mainwindow needs to be able to access these directly
	void saveCurrentCodeToExistingFile(MainWindow *mainWindow);

	void resetCurrentFilePath();
protected:
	bool startBuilding(bool onlyBuild);
	void startRunning();
	virtual void saveFile(std::string filePath);

	MainWindow *mainWindow;
	std::string currentFilePath;

private:
	Tokenizer *tokenizer;
	Compiler *compiler;
	VirtualMachine *virtualMachine;

	QString makeDefaultIvyFolder();
	bool fileHasBeenSavedBefore();
	QString getCurrentFilePathAsQstring();

	static const QString IVY_FOLDER_NAME; //Qstrings can't be initialized in the header, see the implementation file!
};

#endif // BASECONTROLLER_H
