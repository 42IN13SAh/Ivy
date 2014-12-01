#include "basecontroller.h"
#include <qdebug.h>
#include <iostream>
#include "mainwindow.h"

#include "..\..\Tokenizer\Tokenizer.h"
#include "..\..\Tokenizer\BadSyntaxException.h"
#include "..\..\Compiler\Compiler.h"
#include "..\..\Virtual Machine\VirtualMachine.h"
#include "..\Jzon.h"

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

void BaseController::startBuilding(bool onlyBuild)
{
	source->getBottomBar()->clearErrorList();

	std::vector<std::string> list = source->getCodeEditor()->getEditorContent();

	tokenizer = new Tokenizer();
	try
	{
		tokenizer->tokenize(&list[0], list.size());
	}
	catch (BadSyntaxException& e)
	{
		source->getBottomBar()->addError(e.getLineNumber(), e.getLinePosition(), e.what());

		if (onlyBuild)
		{
			delete tokenizer;
		}

		compiler = nullptr;
		return;
	}

	compiler = new Compiler(tokenizer->getTokenList());
	try
	{
		compiler->compile();
	}
	catch (exception& e)
	{
		source->getBottomBar()->addError(0, 0, e.what()); //TODO: fix when compiler has better errorhandling

		if (onlyBuild)
		{
			delete tokenizer;			
			delete compiler;
		}

		compiler = nullptr;
		return;
	}

	if (onlyBuild)
	{
		delete compiler;
		delete tokenizer;
	}
}

void BaseController::startRunning()
{
	startBuilding(false);

	VirtualMachine *virtualMachine = new VirtualMachine();

	if (compiler != nullptr) //compiler is a nullptr when there are builderrors
	{
		try
		{
			virtualMachine->run(compiler->getFirstAction());
		}
		catch (exception e)
		{
			std::cout << e.what();
		}
	}

	delete virtualMachine;
	delete compiler;
	delete tokenizer;
}
