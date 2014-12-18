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
	throw new std::exception;
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
	return ExceptionCodes::NotFound;
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

SymbolTableItemsToBeDeleted *SymbolTable::getItemsToDelete(std::vector<FunctionSymbol *>functionSymbolsToSkip, std::vector<Symbol *>symbolsToSkip){
	SymbolTableItemsToBeDeleted *items = new SymbolTableItemsToBeDeleted();
	for each (Symbol *symbol in this->symbols)
	{
		if (!(std::find(symbolsToSkip.begin(), symbolsToSkip.end(), symbol) != symbolsToSkip.end())) {
			//symbol should not be skipped, add it to items
			items->addSymbol(*symbol);
		}
	}
	for each (FunctionSymbol *functionSymbol in this->fSymbols)
	{
		if (!(std::find(functionSymbolsToSkip.begin(), functionSymbolsToSkip.end(), functionSymbol) != functionSymbolsToSkip.end())) {
			//symbol should not be skipped, add it to items
			items->addFunctionSymbol(*functionSymbol);
		}
	}
	/*We now have everything in THIS symboltable, but every functionsymbol has a potential symboltable of it's own. Therefore, we need to loop through all
	the functionsymbols we have found (i.e. we didn't have to skip), and go through their symbol tables to check for any symbols or functionsymbols we haven't
	found in here yet. This can ofcourse mean that we could find a functionsymbol, that has another functinosymbol in his symboltable, and THAT functionsymbol
	as well, etc. This means that this function will be called recursively untill we 'resolved' all functionsymbols and their contents.
	*/
	std::vector<FunctionSymbol *>allFunctionSymbolsToSkip;
	allFunctionSymbolsToSkip.insert(allFunctionSymbolsToSkip.end(), functionSymbolsToSkip.begin(), functionSymbolsToSkip.end());
	std::vector<FunctionSymbol *>itemFunctionSymbols = items->getFunctionSymbols();
	allFunctionSymbolsToSkip.insert(allFunctionSymbolsToSkip.end(), itemFunctionSymbols.begin(), itemFunctionSymbols.end());

	std::vector<Symbol *>allSymbolsToSkip;
	allSymbolsToSkip.insert(allSymbolsToSkip.end(), symbolsToSkip.begin(), symbolsToSkip.end());
	std::vector<Symbol *>itemSymbols = items->getSymbols();
	allSymbolsToSkip.insert(allSymbolsToSkip.end(), itemSymbols.begin(), itemSymbols.end());

	for each (FunctionSymbol *functionSymbol in items->getFunctionSymbols())
	{
		SymbolTableItemsToBeDeleted *functionSymbolItems = functionSymbol->getSymbolTable()->getItemsToDelete(allFunctionSymbolsToSkip, allSymbolsToSkip);
		std::vector<FunctionSymbol *>functionSymbolsFromFunctionSymbolItem = functionSymbolItems->getFunctionSymbols();
		std::vector<Symbol *>symbolsFromFunctionSymbolItem = functionSymbolItems->getSymbols();
		items->insertIntoFunctionSymbols(functionSymbolsFromFunctionSymbolItem);
		items->insertIntoSymbols(symbolsFromFunctionSymbolItem);

		delete functionSymbolItems;
	}
	return items;
}