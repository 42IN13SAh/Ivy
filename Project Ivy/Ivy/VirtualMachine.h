#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <stack>
#include <boost/any.hpp>
#include "Compiler.h"
#include "TokenType.h"

// Exceptions
#include "TypeMismatchException.h"
#include "DivideByZeroException.h"
#include "UnexpectedOperatorException.h"
#include "EmptyResultStackException.h"
#include "VariableNotFoundException.h"
#include "BadCastException.h"

class VirtualMachine
{
public:
	VirtualMachine(SymbolTable* symbolTable);
	VirtualMachine();
	~VirtualMachine();
	void run(Action *firstAction);
	void addVariable(std::string name, boost::any value, SymbolTable& symbolTable);
	void updateVariable(std::string name, boost::any value, SymbolTable& symbolTable);
private:
	SymbolTable* globalSymbolTable;
	Action* currentAction;
	void executeAction(CompilerToken* compilerToken, SymbolTable& symbolTable);
	void executeAction(ReturnValueCompilerToken* compilerToken, SymbolTable& symbolTable);
	void executeAction(AssignCompilerToken* compilerToken, SymbolTable& symbolTable);
	boost::any executeAction(FunctionCompilerToken* compilerToken, SymbolTable& symbolTable, Action* fAction);
	void executeAction(VarCompilerToken* compilerToken, SymbolTable& symbolTable);
	boost::any executeInternalFunction(std::string name, FunctionCompilerToken* compilerToken, SymbolTable& symbolTable);
	bool executeAction(ConditionCompilerToken* compilerToken, SymbolTable& symbolTable);
	bool exNumber(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack);
	bool exString(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack);
	bool exBool(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack);
	bool exStringNumber(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack);
	bool exNumberString(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack);
	boost::any getReturnValue(ReturnValueCompilerToken*, SymbolTable& symbolTable);
	boost::any getVarValue(VarCompilerToken*, SymbolTable& symbolTable);

	template<class T>
	T cast(boost::any val) {
		try {
			return boost::any_cast<T>(val);
		} catch (std::exception& e) {
			throw BadCastException(typeid(T).name(), val.type().name());
		}
	}
};

