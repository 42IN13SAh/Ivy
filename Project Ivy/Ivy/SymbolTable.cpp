#include <exception>
#include "SymbolTable.h"
#include "ExceptionCodes.h"

SymbolTable::SymbolTable(int level, std::string functionName)
{

}

SymbolTable::SymbolTable()
{

}

SymbolTable::~SymbolTable()
{
	for (int i = 0; i < symbols.size(); i++){
		delete symbols[i];
	}
	for (int i = 0; i < fSymbols.size(); i++){
		delete fSymbols[i];
	}
}

void SymbolTable::clearSymbolTable(){
	for (int i = 0; i < symbols.size(); i++){
		symbols[i]->setValue(NULL);
	}
}

bool SymbolTable::addSymbolToTable(std::string name)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
		{
			//throw new std::exception;
			return false;
		}
	}
	symbols.push_back(new Symbol(name));
	return true;
}

bool SymbolTable::addSymbolToTable(std::string name, boost::any value)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
		{
			//throw new std::exception;
			return false;
		}
	}
	symbols.push_back(new Symbol(name, value));
	return true;
}


void SymbolTable::updateExistingSymbol(std::string name, boost::any value)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
		{
			symbol->setValue(value);
			return;
		}
	}
	throw std::exception();
}

bool SymbolTable::hasSymbol(std::string name)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
			return true;
	}
	return false;
}

boost::any SymbolTable::getValue(std::string name)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
			return symbol->getValue();
	}
	return ExceptionCodes::VarNotFound;
}

bool SymbolTable::addFunctionSymbol(FunctionSymbol* fs) 
{
	if (getFunctionSymbol(fs->getName(), fs->getArgumentNr()) == nullptr) {
		fSymbols.push_back(fs);
		return true;
	}
	return false;
}

bool SymbolTable::hasFunctionSymbolWithName(std::string name) {
	for each(FunctionSymbol* fs in fSymbols) {
		if (fs->getName() == name)
			return true;
	}
	return false;
}

FunctionSymbol* SymbolTable::getFunctionSymbol(std::string name, int argNr) 
{
	for each(FunctionSymbol* fs in fSymbols) {
		if (fs->getName() == name && fs->getArgumentNr() == argNr)
			return fs;
	}
	return nullptr;
}

std::vector<Symbol *> SymbolTable::getAllSymbols()
{
	return this->symbols;
}

std::vector<FunctionSymbol *> SymbolTable::getAllFunctionSymbols(){
	return this->fSymbols;
}