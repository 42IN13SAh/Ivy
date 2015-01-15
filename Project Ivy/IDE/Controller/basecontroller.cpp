#include <qdebug.h>
#include <iostream>
#include <fstream>

#include "qmessagebox.h"
#include "qfiledialog.h"
#include "qstandardpaths.h"
#include "basecontroller.h"
#include "mainwindow.h"
#include "Tokenizer.h"
#include "BaseException.h"
#include "Compiler.h"
#include "VirtualMachine.h"
#include "Jzon.h"

const QString BaseController::IVY_FOLDER_NAME = "/Ivy";

BaseController::BaseController(MainWindow * mainWindow) : QObject()
{
	this->mainWindow = mainWindow;
	this->resetCurrentFilePath();
}

BaseController::~BaseController()
{
	delete virtualMachine;
	delete compiler;
	delete tokenizer;
}

bool BaseController::startBuilding(bool onlyBuild, bool showConsoleOutput)
{
	bool buildSucceeded = true;

	emit clearBeforeBuilding();

	if (showConsoleOutput) {
		std::cout << "Build started.";
	}

	std::vector<std::string> list = mainWindow->getCodeEditor()->getEditorContent();

	tokenizer = new Tokenizer();

	tokenizer->tokenize(&list[0], list.size());
	if (tokenizer->getErrorList().size() > 0) {
		buildSucceeded = false;

		if (showConsoleOutput) {
			std::cout << "Syntax error(s) found. See the Errors tab for specific infomation.";
			std::cout << "Build failed.";
		}

		for each(BaseException e in tokenizer->getErrorList()) {
			emit addError(e.getLineNumber(), e.getLinePosition(), QString(e.what()));
		}

		delete tokenizer;

		emit finishedBuilding(buildSucceeded);

		return buildSucceeded;
	}

	compiler = new Compiler(tokenizer->getTokenList());
	compiler->compile();
	makeCompleterModel(compiler->getAllFunctionAndVariableNames());
	if (compiler->getErrorList().size() > 0) {
		buildSucceeded = false;

		if (showConsoleOutput) {
			std::cout << "Compile time error(s) found. See the Errors tab for specific infomation.";
			std::cout << "Build failed.";
		}

		for each(BaseException e in compiler->getErrorList()) {
			emit addError(e.getLineNumber(), e.getLinePosition(), e.what());
		}

		delete compiler;

		emit finishedBuilding(buildSucceeded);

		return buildSucceeded;
	}

	if (showConsoleOutput) {
		std::cout << "Build succeeded.";
	}

	if (onlyBuild)
	{
		compiler->~Compiler();
		tokenizer->~Tokenizer();
	}

	emit finishedBuilding(buildSucceeded);

	return buildSucceeded;
}

void BaseController::startRunning()
{
	bool buildSucceeded = startBuilding(false, true);

	if (buildSucceeded)
	{
		std::cout << "Running.\n";

		VirtualMachine *virtualMachine = new VirtualMachine(compiler->getSymbolTable());

		if (compiler != nullptr) //compiler is a nullptr when there are builderrors
		{
			try
			{
				virtualMachine->run(compiler->getFirstAction());
				std::cout << "\nProgram has finished successfully.";
			}
			catch (std::exception& e)
			{
				std::cout << e.what();
				std::cout << "\nA runtime error has occurred.";
				std::cout << "Program has unexpectedly finished.";
			}
		}
	}
}

void BaseController::saveCurrentCodeToNewFile(MainWindow *parentWindow){
	//First, make an Ivy folder for all files in the user's home directory
	QString ivyFolderPath = makeDefaultIvyFolder();

	//See if we need to change the starting directory for the dialog
	if (this->fileHasBeenSavedBefore()){
		ivyFolderPath = this->getCurrentFilePathAsQstring();
	}

	//open a save file dialog in that directory
	std::string filePath = QFileDialog::getSaveFileName(parentWindow, "Save", ivyFolderPath, QString::fromStdString("Ivy File (*.ivy)")).toStdString();

	if (!filePath.empty()){ //it CAN be empty if the user selected cancel
		//filePath is valid, so don't forget to save this filePath!
		this->currentFilePath = filePath;
		//Also save the contents for comparisson later so we know if there are unsaved changes
		this->setLastSavedEditorContents(parentWindow->getCodeEditor()->getEditorContent());
		saveFile(filePath);
	}
}

void BaseController::saveCurrentCodeToExistingFile(MainWindow *parentWindow){
	//First, make an Ivy folder for all files in the user's home directory
	QString ivyFolderPath = makeDefaultIvyFolder();

	//Now, determine if the user actually has been working from an existing file (if he saved before).
	if (this->fileHasBeenSavedBefore()){
		ivyFolderPath = this->getCurrentFilePathAsQstring();
		//Also save the contents for comparisson later so we know if there are unsaved changes
		this->setLastSavedEditorContents(parentWindow->getCodeEditor()->getEditorContent());
		saveFile(ivyFolderPath.toStdString());
	}
	else{
		//Invalid path, while the user did not select the save as option. We don't know where to save to, so just use the save as function instead
		this->saveCurrentCodeToNewFile(parentWindow);
	}
}

void BaseController::resetCurrentFilePath(){
	this->currentFilePath = std::string();
}

void BaseController::openFileAction(CodeEditor *editor, MainWindow *parentWindow){
	int result = this->promptActionForLeavingCurrentFile(editor, parentWindow);
	const int YES = QMessageBox::Yes;
	const int NO = QMessageBox::No;
	const int CANCEL = QMessageBox::Cancel;
	if (result == YES){
		//Save first, always use save as in this case
		this->saveCurrentCodeToNewFile(parentWindow);
		this->showOpenFileDialog(parentWindow);
	}
	else if (result == NO){
		//Go straight to opening
		this->showOpenFileDialog(parentWindow);
	}
	else
	{
		//Aperantly, the user does not want to open after all; do nothing
		return;
	}
}

void BaseController::startNewFile(MainWindow *parentWindow){
	int result = this->promptActionForLeavingCurrentFile(parentWindow->getCodeEditor(), parentWindow);
	const int YES = QMessageBox::Yes;
	const int NO = QMessageBox::No;
	const int CANCEL = QMessageBox::Cancel;
	if (result == CANCEL){
		return;
	}
	else if (result == YES){
		//Save first, always use save as in this case
		this->saveCurrentCodeToNewFile(parentWindow);
	}
	parentWindow->resetEditor();
	this->currentFilePath = "";
	this->setLastSavedEditorContents(mainWindow->getCodeEditor()->getEditorContent());
	parentWindow->setAndSaveWindowTitle("New File - " + parentWindow->getDefaultWindowTitle());
}

void BaseController::saveFile(std::string filePath){
	std::vector<std::string> outputList = mainWindow->getCodeEditor()->getEditorContent();
	std::ofstream file(filePath, std::ofstream::trunc);
	//about std::ofstream::trunc: this mode overwrites the entire file, see http://www.cplusplus.com/reference/fstream/ofstream/ofstream/

	for (size_t i = 0; i < outputList.size(); i++)
	{
		file << outputList[i];
		if (i + 1 < outputList.size()){ //If it's not the second to last (since then we need to add a new line
			file << std::endl; //TODO: Research alternative since this MIGHT give problems with Unix based systems, but not sure (conflicting info on google)
		}
	}

	file.close();
}

QString BaseController::makeDefaultIvyFolder(){
	QString ivyFolderPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
	ivyFolderPath.append(this->IVY_FOLDER_NAME);
	QDir::home().mkdir(ivyFolderPath); //Returns false if the folder already exists, so no need to check for anything

	//return the full path so other functions can use it
	return ivyFolderPath;
}

bool BaseController::fileHasBeenSavedBefore(){
	QString currentQStringFilePath = getCurrentFilePathAsQstring();

	QFileInfo fileInfo(currentQStringFilePath); //Gives access to easy check functions
	if (!this->currentFilePath.empty() && fileInfo.exists() && fileInfo.isFile()){
		//The currentFilePath is valid, meaning the user is working on a file that has already been saved before.
		return true;
	}
	return false;
}

QString BaseController::getCurrentFilePathAsQstring() {
	return QString::fromStdString(this->currentFilePath);
}

void BaseController::openFile(std::string filePath, CodeEditor *editor){
	std::ifstream fileStream(filePath);

	std::string contents;
	std::stringstream buffer;
	buffer << fileStream.rdbuf();

	contents = buffer.str();

	editor->clear();
	editor->insertPlainText(QString::fromStdString(contents));
	this->currentFilePath = filePath;
	this->setLastSavedEditorContents(mainWindow->getCodeEditor()->getEditorContent());
}

void BaseController::showOpenFileDialog(MainWindow *parentWindow){
	//First, make an Ivy folder for all files in the user's home directory
	QString ivyFolderPath = makeDefaultIvyFolder();

	//See if we need to change the starting directory for the dialog
	if (this->fileHasBeenSavedBefore()){
		ivyFolderPath = this->getCurrentFilePathAsQstring();
	}

	QString filePath = QFileDialog::getOpenFileName(parentWindow,
		tr("Open Script File"), ivyFolderPath, tr("Ivy Files (*.ivy)"));

	if (!filePath.isEmpty()){
		this->openFile(filePath.toStdString(), parentWindow->getCodeEditor());
		parentWindow->setAndSaveWindowTitle(filePath + " - " + parentWindow->getDefaultWindowTitle());
	}
}

int BaseController::promptActionForLeavingCurrentFile(CodeEditor *editor, MainWindow *parentWindow)
{
	int result = QMessageBox::No; //default is to go straight to openeing
	if (editor->getEditorContent()[0].size() > 0){
		//User has typed in the editor check if the contents differ. If it is a new file, the called function below will return true as well
		if (this->contentsDiffer(editor->getEditorContent(), this->getLastSavedEditorContents())){
			//Contents differ, but the user wants to open a new file. Ask if he wants to save first.
			result = parentWindow->showUnsavedChangesDialog();
		}
	}
	return result;
}

bool BaseController::contentsDiffer(std::vector<std::string> currentContents, std::vector<std::string> contentToCompareTo){
	/*	Notes:	- If editor is empty, there will still be 1 string element in the currentContents vector: an empty string object.
				- The default value for lastSavedEditorContents (usually passed in contentToCompareTo) is an empty vector
	*/
	if (currentContents.size() != contentToCompareTo.size()){ //If sizes are not the same, there is no way the contents are.
		return true;
	}
	else{
		for (size_t i = 0; i < currentContents.size(); i++)
		{
			if (currentContents[i].compare(contentToCompareTo[i]) != 0){ //If the strings are NOT the same
				return true;
			}
		}
	}
	return false;
}

std::vector<std::string> BaseController::getLastSavedEditorContents(){
	return this->lastSavedEditorContents;
}

void BaseController::setLastSavedEditorContents(std::vector<std::string> newContents){
	this->lastSavedEditorContents = newContents;
}

void BaseController::makeCompleterModel(std::vector<std::string> list)
{
	QList<QString> wordList;

	for each (std::string s in list)
	{
		wordList << QString::fromStdString(s);
	}

	emit setCompleterModel(wordList);
}
