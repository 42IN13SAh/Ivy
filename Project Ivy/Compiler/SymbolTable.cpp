#include "SymbolTable.h"

SymbolTable::SymbolTable(int level, string functionName)
{

}

SymbolTable::SymbolTable()
{

}

SymbolTable::~SymbolTable()
{
}


void SymbolTable::addSymbolToTable(string name)
{
	//check if there isn't already an existing variable with the same name, in that case an exception is thrown
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
		{
			throw new exception; //TODO: better exception handling
		}
	}

	symbols.push_back(new Symbol(name));
}

void SymbolTable::addSymbolToTable(string name, boost::any value)
{
	//check if there isn't already an existing variable with the same name, in that case an exception is thrown
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
		{
			throw new exception; //TODO: better exception handling
		}
	}

	symbols.push_back(new Symbol(name, value));
}


void SymbolTable::updateExistingSymbol(string name, boost::any value)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
		{
			symbol->setValue(value);
			return;
		}
	}

	//symbol was not found in the symboltable
	throw new exception; //TODO: better exception handling
}

bool SymbolTable::hasSymbol(string name)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
			return true;
	}
	return false;
}

boost::any SymbolTable::getValue(string name)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
			return symbol->getValue();
	}

	throw new exception; //Symbol not found. TODO: better exception handling
}

void SymbolTable::addFunctionSymbol(FunctionSymbol* fs) {
	if (getFunctionSymbol(fs->getName(), fs->getArgumentNr()) == nullptr) {
		fSymbols.push_back(fs);
	}
	else {
		throw new exception; // Already exists
	}
}

FunctionSymbol* SymbolTable::getFunctionSymbol(std::string name, int argNr) {
	for each(FunctionSymbol* fs in fSymbols) {
		if (fs->getName() == name && fs->getArgumentNr() == argNr)
			return fs;
	}
	return nullptr;
}

std::vector<Symbol *> SymbolTable::getAllSymbols(){
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