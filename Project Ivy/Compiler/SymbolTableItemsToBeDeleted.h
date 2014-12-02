#pragma once
#include <vector>

#include "FunctionSymbol.h"
#include "Symbol.h"

/*
	This class serves as a wrapper class for all the items from the symboltable (i.e. the symbols and functionsymbols) that have to be deleted.
	Because of possible recursion and duplicity, it's better to clean used objects from the heap with a recursive function. The problem with that,
	however, is that there are two types of objects that are closely related and need to be cleaned up at the same time: symbols and functionsymbols.
	With a recursive function, you can't return/receive more than one result from a nested call:

	(pseudo-code:)
	func recursive_func(){
		var a = this.get_some_var_value();
		var b = this.get_some_other_var_value();

		if (this.c != null){
			//stil got some more to go!
			return this.c.recursive_func();
		}
		return a,b; // <-- ERROR! can't return a and b at the same time!
	}
	
	Therefore, we put the results in a wrapper class to return that. Also note that a struct will NOT work, since they are created on the stack, which means that
	as soon as you return from a nested call, that struct is out of scope and deleted/removed.
*/
class SymbolTableItemsToBeDeleted
{
public:
	SymbolTableItemsToBeDeleted();
	~SymbolTableItemsToBeDeleted();

	std::vector<FunctionSymbol *>getFunctionSymbols();
	std::vector<Symbol *>getSymbols();
	void addFunctionSymbol(FunctionSymbol &newItem);
	void addSymbol(Symbol &newItem);
	void insertIntoFunctionSymbols(std::vector<FunctionSymbol *> &newItems);
	void insertIntoSymbols(std::vector<Symbol *> &newItems);
private:
	std::vector<FunctionSymbol *>functionSymbols;
	std::vector<Symbol *>symbols;
};

