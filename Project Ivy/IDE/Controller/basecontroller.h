#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H
#include <string>
#include <qobject.h>

#include "qstring.h"
#include "codeeditor.h"

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
	void saveCurrentCodeToNewFile(MainWindow *parentWindow); //Two public functions since mainwindow needs to be able to access these directly
	void saveCurrentCodeToExistingFile(MainWindow *parentWindow);
	void resetCurrentFilePath();
	void openFileAction(CodeEditor *editor, MainWindow *parentWindow);
	void startNewFile(MainWindow *parentWindow);

	bool fileHasBeenSavedBefore();
signals:
	void clearBeforeBuilding();
	void addError(int, int, QString);
	void setCompleterModel(QList<QString>);
	void finishedBuilding(bool);

protected:
	MainWindow *mainWindow;
	std::string currentFilePath;
	virtual void saveFile(std::string filePath);

private:
	Tokenizer *tokenizer;
	Compiler *compiler;
	VirtualMachine *virtualMachine;
	QString makeDefaultIvyFolder();
	QString getCurrentFilePathAsQstring();

	void openFile(std::string filePath, CodeEditor *editor);
	void showOpenFileDialog(MainWindow *parentWindow);

	int promptActionForLeavingCurrentFile(CodeEditor *editor, MainWindow *parentWindow);
	bool contentsDiffer(std::vector<std::string> currentContents, std::vector<std::string> contentToCompareTo);
	std::vector<std::string> getLastSavedEditorContents();
	void setLastSavedEditorContents(std::vector<std::string> newContents);

	std::vector<std::string> lastSavedEditorContents;
	static const QString IVY_FOLDER_NAME; //Qstrings can't be initialized in the header, see the implementation file!

	void makeCompleterModel(std::vector<std::string>);
};

#endif // BASECONTROLLER_H
