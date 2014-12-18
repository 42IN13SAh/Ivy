#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H
#include <string>
#include "qstring.h"

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
	void saveCurrentCodeToNewFile(MainWindow *mainWindow); //Two public functions since mainwindow needs to be able to access these directly
	void saveCurrentCodeToExistingFile(MainWindow *mainWindow);
	void resetCurrentFilePath();

signals:
	void clearBeforeBuilding();
	void addError(int, int, QString);

protected:
	MainWindow *mainWindow;
	std::string currentFilePath;
	virtual void saveFile(std::string filePath);

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
