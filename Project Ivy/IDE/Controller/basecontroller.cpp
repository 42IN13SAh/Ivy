#include <qdebug.h>
#include <iostream>
#include <fstream>
#include <windows.h>

#include "qstring.h"
#include "qfiledialog.h"
#include "basecontroller.h"
#include "mainwindow.h"
#include "Tokenizer.h"
#include "BaseException.h"
#include "Compiler.h"
#include "VirtualMachine.h"
#include "Jzon.h"

BaseController::BaseController(MainWindow * source)
{
	this->source = source;
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

	source->getBottomBar()->clearConsole();
	source->getBottomBar()->clearErrorList();

	std::cout << "Build started.";

	std::vector<std::string> list = source->getCodeEditor()->getEditorContent();

	tokenizer = new Tokenizer();

	tokenizer->tokenize(&list[0], list.size());
	if (tokenizer->getErrorList().size() > 0) {
		buildSucceeded = false;

		std::cout << "Syntax error(s) found. See the Errors tab for specific infomation.";
		std::cout << "Build failed.";

		for each(BaseException e in tokenizer->getErrorList()) {
			source->getBottomBar()->addError(e.getLineNumber(), e.getLinePosition(), e.what());
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

		source->getBottomBar()->addError(0, 0, e.what()); //TODO: fix when compiler has better errorhandling

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

void BaseController::saveCurrentFile(){
	if (!this->currentFilePath.empty() && this->fileExists(this->currentFilePath)){
		saveNewFile(this->currentFilePath);
	}
	else{
		//No filepath detected or the old filepath doesn't exist anymore: prompt for new file location
		this->currentFilePath = QFileDialog::getSaveFileName(this->source, "Save", QString::fromStdString(this->ExePath()), QString::fromStdString("Image Files (*.png *.jpg *.bmp)")).toStdString();
	}
}

void BaseController::saveNewFile(std::string filePath){
	std::vector<std::string> outputList = source->getCodeEditor()->getEditorContent();
	std::ofstream file(filePath);

	for (size_t i = 0; i < outputList.size(); i++)
	{
		file << outputList[i] << endl;
	}

	file.close();
}

#include <sys/stat.h>
// Function: fileExists
/**
Check if a file exists
@param[in] filename - the name of the file to check

@return    true if the file exists, else false

*/
bool BaseController::fileExists(const std::string& filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}

std::string BaseController::ExePath() {
	wchar_t buffer[MAX_PATH];
	char charBuffer[MAX_PATH];
	char defChar = ' ';
	GetModuleFileName(NULL, buffer, MAX_PATH);

	WideCharToMultiByte(CP_ACP, 0, buffer, -1, charBuffer, 260, &defChar, NULL);
	std::string::size_type pos = std::string(charBuffer).find_last_of("\\/");
	return std::string(charBuffer).substr(0, pos);
}