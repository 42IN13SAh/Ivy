#include "basecontroller.h"
#include <qdebug.h>
#include <iostream>
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
	compiler->compile();
	if (compiler->getErrorList().size() > 0) {
		buildSucceeded = false;

		std::cout << "Compile time error(s) found. See the Errors tab for specific infomation.";
		std::cout << "Build failed.";

		for each(BaseException e in compiler->getErrorList()) {
			source->getBottomBar()->addError(e.getLineNumber(), e.getLinePosition(), e.what());
		}

		delete compiler;
		return buildSucceeded;
	}
	//try
	//{
	//	compiler->compile();
	//}
	//catch (std::exception& e)
	//{
	//	buildSucceeded = false;

	//	std::cout << "Compile time error(s) found. See the Errors tab for specific infomation.";
	//	std::cout << "Build failed.";

	//	source->getBottomBar()->addError(0, 0, e.what()); //TODO: fix when compiler has better errorhandling

	//	if (onlyBuild)
	//	{
	//		delete tokenizer;			
	//		delete compiler;
	//	}

	//	compiler = nullptr;
	//	return buildSucceeded;
	//}

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
