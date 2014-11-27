#include "basecontroller.h"
#include <qdebug.h>
#include <iostream>
#include "mainwindow.h"

#include "..\..\Tokenizer\Tokenizer.h"
#include "..\..\Tokenizer\BadSyntaxException.h"
#include "..\..\Compiler\Compiler.h"
#include "..\Jzon.h"
#include <boost\regex.hpp>

BaseController::BaseController(MainWindow * source)
{
	this->source = source;
}

void BaseController::startBuilding(){
	std::vector<std::string> list = source->getEditorContent();

	Tokenizer *tokenizer = new Tokenizer();

	try
	{
		tokenizer->tokenize(&list[0], list.size());
	}
	catch (BadSyntaxException& e)
	{
		std::cout << e.what();
	}

	//Currently not compiling until errorhandling in compiler is decent
	//Compiler *compiler = new Compiler(tokenizer->getTokenList());
	//compiler->compile();
}

void BaseController::startRunning(){
    //TODO implement
}
