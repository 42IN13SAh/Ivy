#include <qdebug.h>
#include <iostream>
#include <fstream>

#include "qfiledialog.h"
#include "qstandardpaths.h"
#include "basecontroller.h"
#include "mainwindow.h"
#include "Tokenizer.h"
#include "BaseException.h"
#include "Compiler.h"
#include "VirtualMachine.h"
#include "Jzon.h"

BaseController::BaseController(MainWindow * mainWindow)
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

bool BaseController::startBuilding(bool onlyBuild)
{
	bool buildSucceeded = true;

	mainWindow->getBottomBar()->clearConsole();
	mainWindow->getBottomBar()->clearErrorList();

	std::cout << "Build started.";

	std::vector<std::string> list = mainWindow->getCodeEditor()->getEditorContent();

	tokenizer = new Tokenizer();

	tokenizer->tokenize(&list[0], list.size());
	if (tokenizer->getErrorList().size() > 0) {
		buildSucceeded = false;

		std::cout << "Syntax error(s) found. See the Errors tab for specific infomation.";
		std::cout << "Build failed.";

		for each(BaseException e in tokenizer->getErrorList()) {
			mainWindow->getBottomBar()->addError(e.getLineNumber(), e.getLinePosition(), e.what());
		}

		delete tokenizer;
		return buildSucceeded;
	}

	compiler = new Compiler(tokenizer->getTokenList());

	try
	{
		compiler->compile();
	}
	catch (std::exception& e)
	{
		buildSucceeded = false;

		std::cout << "Compile time error(s) found. See the Errors tab for specific infomation.";
		std::cout << "Build failed.";

		mainWindow->getBottomBar()->addError(0, 0, e.what()); //TODO: fix when compiler has better errorhandling

		if (onlyBuild)
		{
			delete tokenizer;
			delete compiler;
		}

		compiler = nullptr;
		return buildSucceeded;
	}

	std::cout << "Build succeeded.";

	if (onlyBuild)
	{
		delete compiler;
		delete tokenizer;
	}

	return buildSucceeded;
}

void BaseController::startRunning()
{
	bool buildSucceeded = startBuilding(false);

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
			catch (std::exception e)
			{
				std::cout << "\nA runtime error has occurred.";
				std::cout << "Program has unexpectedly finished.";
			}
		}
	}
}

void BaseController::saveCurrentCodeToNewFile(MainWindow *mainWindow){
	//First, make an Ivy folder for all files in the user's home directory
	QString ivyFolderPath = makeDefaultIvyFolder();

	//See if we need to change the starting directory for the dialog
	if (this->fileHasBeenSavedBefore()){
		ivyFolderPath = this->getCurrentFilePathAsQstring();
	}

	//open a save file dialog in that directory
	std::string filePath = QFileDialog::getSaveFileName(mainWindow, "Save", ivyFolderPath, QString::fromStdString("Ivy File (*.ivy)")).toStdString();

	if (!filePath.empty()){ //it CAN be empty if the user selected cancel
		//filePath is valid, so don't forget to save this filePath!
		this->currentFilePath = filePath;
		saveFile(filePath);
	}
}

void BaseController::saveCurrentCodeToExistingFile(MainWindow *mainWindow){
	//First, make an Ivy folder for all files in the user's home directory
	QString ivyFolderPath = makeDefaultIvyFolder();

	//Now, determine if the user actually has been working from an existing file (if he saved before).
	if (this->fileHasBeenSavedBefore()){
		ivyFolderPath = this->getCurrentFilePathAsQstring();
		saveFile(ivyFolderPath.toStdString());
	}
	else{
		//Invalid path, while the user did not select a save as option. We don't know where to save to, so just use the save as function instead
		this->saveCurrentCodeToNewFile(mainWindow);
	}
}

void BaseController::resetCurrentFilePath(){
	this->currentFilePath = std::string();
}

void BaseController::saveFile(std::string filePath){
	std::vector<std::string> outputList = mainWindow->getCodeEditor()->getEditorContent();
	std::ofstream file(filePath, std::ofstream::trunc);
	//about std::ofstream::trunc: this moed overwrites the entire file, see http://www.cplusplus.com/reference/fstream/ofstream/ofstream/

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
	const QString IVY_FOLDER_NAME = "/Ivy";
	QString ivyFolderPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
	ivyFolderPath.append(IVY_FOLDER_NAME);
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