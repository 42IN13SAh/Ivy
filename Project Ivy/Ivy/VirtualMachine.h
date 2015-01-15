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
	void executeAction(boost::shared_ptr<CompilerToken> compilerToken, SymbolTable& symbolTable);
	void executeAction(boost::shared_ptr<ReturnValueCompilerToken> compilerToken, SymbolTable& symbolTable);
	void executeAction(boost::shared_ptr<AssignCompilerToken> compilerToken, SymbolTable& symbolTable);
	boost::any executeAction(boost::shared_ptr<FunctionCompilerToken> compilerToken, SymbolTable& symbolTable, Action* fAction);
	void executeAction(boost::shared_ptr<VarCompilerToken> compilerToken, SymbolTable& symbolTable);
	boost::any executeInternalFunction(std::string name, boost::shared_ptr<FunctionCompilerToken> compilerToken, SymbolTable& symbolTable);
	bool executeAction(boost::shared_ptr<ConditionCompilerToken> compilerToken, SymbolTable& symbolTable);
	bool exNumber(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack);
	bool exString(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack);
	bool exBool(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack);
	bool exStringNumber(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack);
	bool exNumberString(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack);
	bool exNoneCheck(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack);
	boost::any getReturnValue(boost::shared_ptr<ReturnValueCompilerToken> compilerToken, SymbolTable& symbolTable);
	boost::any getVarValue(boost::shared_ptr<VarCompilerToken> compilerToken, SymbolTable& symbolTable);
};

