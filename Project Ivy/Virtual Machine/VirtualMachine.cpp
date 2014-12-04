#include "VirtualMachine.h"
#include "../Compiler/AssignCompilerToken.h"
#include "../Compiler/ConditionCompilerToken.h"
#include "../Compiler/FunctionCompilerToken.h"
#include "../Compiler/ReturnValueCompilerToken.h"
#include "../Compiler/VarCompilerToken.h"
#include "../Compiler/ReturnCompilerToken.h"
#include "ExceptionCodes.h"
#include <string>

VirtualMachine::VirtualMachine()
{
}

VirtualMachine::VirtualMachine(SymbolTable* symbolTable)
{
	globalSymbolTable = symbolTable;
}

VirtualMachine::~VirtualMachine()
{
}

void VirtualMachine::run(Action *firstAction)
{
	currentAction = firstAction;
	while (currentAction != nullptr)
	{
		CompilerToken* compilerToken = currentAction->getCompilerToken();
		executeAction(compilerToken, *globalSymbolTable);
	}
}

void VirtualMachine::addVariable(std::string name, boost::any value, SymbolTable& symbolTable) 
{
	symbolTable.addSymbolToTable(name, value);
}

void VirtualMachine::updateVariable(string name, boost::any value, SymbolTable& symbolTable)
{
	if (symbolTable.hasSymbol(name)){
		symbolTable.updateExistingSymbol(name, value);
	}
	else{
		globalSymbolTable->updateExistingSymbol(name, value);
	}
}

void VirtualMachine::executeAction(CompilerToken* ct, SymbolTable& symbolTable){
	if (ct != nullptr){
		if (typeid(*ct) == typeid(ReturnValueCompilerToken)){
			executeAction((ReturnValueCompilerToken*)ct, symbolTable);
			currentAction = currentAction->getNextAction();
		}
		else if (typeid(*ct) == typeid(AssignCompilerToken)){
			executeAction((AssignCompilerToken*)ct, symbolTable);
			currentAction = currentAction->getNextAction();
		}
		else if (typeid(*ct) == typeid(FunctionCompilerToken)){
			executeAction((FunctionCompilerToken*)ct, symbolTable, currentAction);
		}
		else if (typeid(*ct) == typeid(ConditionCompilerToken)){
			if (executeAction((ConditionCompilerToken*)ct, symbolTable)){
				currentAction = currentAction->getNextAction();
			}
			else{
				currentAction = currentAction->getFalseAction();
			}
		}
		else if (typeid(*ct) == typeid(VarCompilerToken)){
			executeAction((VarCompilerToken*)ct, symbolTable);
			currentAction = currentAction->getNextAction();
		}
	}
	else{
		currentAction = currentAction->getNextAction();
	}
}

void VirtualMachine::executeAction(ReturnValueCompilerToken* compilerToken, SymbolTable& symbolTable) {
	getReturnValue(compilerToken, symbolTable);
}

void VirtualMachine::executeAction(AssignCompilerToken* compilerToken, SymbolTable& symbolTable)
{
	boost::any val = getVarValue(&VarCompilerToken(compilerToken->getName()), symbolTable);
	boost::any newVal = getReturnValue(compilerToken->getReturnValue(), symbolTable);
	switch (compilerToken->getAssignOp()) {
	case TokenType::AssignmentOperator: val = newVal; break;
	case TokenType::AddThenAssignOperator:
	{
											 if (val.type() == typeid(std::string)){
												 val = boost::any_cast<std::string>(val)+boost::any_cast<std::string>(newVal);
											 }
											 else{
												 val = boost::any_cast<double>(val)+boost::any_cast<double>(newVal);
											 }
											 break;
	}
	case TokenType::MinusThenAssignOperator:
		val = boost::any_cast<double>(val)-boost::any_cast<double>(newVal);
		break;
	case TokenType::DivideThenAssignOperator:
		val = boost::any_cast<double>(val) / boost::any_cast<double>(newVal);
		break;
	case TokenType::MultiplyThenAssignOperator:
		val = boost::any_cast<double>(val)* boost::any_cast<double>(newVal);
		break;
	}
	updateVariable(compilerToken->getName(), val, symbolTable);
}

boost::any VirtualMachine::executeAction(FunctionCompilerToken* compilerToken, SymbolTable& symbolTable, Action* fAction)
{
	boost::any returnValue = nullptr;
	FunctionSymbol* fs = globalSymbolTable->getFunctionSymbol(compilerToken->getName(), compilerToken->getArguments().size());
	if (fs->isInternal()){
		executeInternalFunction(fs->getName(), compilerToken, symbolTable);
	}
	else{
		FunctionCompilerToken* fct = (FunctionCompilerToken*)fs->getStartAction()->getCompilerToken();
		std::vector<std::string> argNames = fct->getArgumentNames();
		for (int i = 0; i < argNames.size(); i++) {
				fs->getSymbolTable()->addSymbolToTable(argNames[i], getReturnValue(compilerToken->getArguments()[i], symbolTable));
		}
		currentAction = fs->getStartAction()->getNextAction();
		while (currentAction != fs->getEndAction()){
			if (currentAction->getCompilerToken() != nullptr  && typeid(*currentAction->getCompilerToken()) == typeid(ReturnCompilerToken)) {
				returnValue = getReturnValue(((ReturnCompilerToken*)currentAction->getCompilerToken())->getReturnValueCompilerToken(), *fs->getSymbolTable());
				currentAction = fAction;
				return returnValue;
			}
			else{
				executeAction(currentAction->getCompilerToken(), *fs->getSymbolTable());
			}
		}
		currentAction = fAction->getNextAction();
	}
	return returnValue;
}

boost::any VirtualMachine::executeInternalFunction(std::string name, FunctionCompilerToken* compilerToken, SymbolTable& symbolTable){
	IInternalFunction* fnc = InternalFunctionFactory::Instance()->Create(name);
	std::vector<boost::any> args;
	for each(ReturnValueCompilerToken* rvct in compilerToken->getArguments()) {
		args.push_back(getReturnValue(rvct, symbolTable));
	}
	currentAction = currentAction->getNextAction();
	fnc->Execute(args);
	return fnc->GetResult();
}

bool VirtualMachine::executeAction(ConditionCompilerToken* compilerToken, SymbolTable& symbolTable)
{
	if (boost::any_cast<bool>(getReturnValue(compilerToken->getReturnValueCompilerToken(), symbolTable))){
		return true;
	}
	else{
		return false;
	}
}

void VirtualMachine::executeAction(VarCompilerToken* compilerToken, SymbolTable& symbolTable)
{
	getVarValue(compilerToken, symbolTable);
}

boost::any VirtualMachine::getVarValue(VarCompilerToken* compilerToken, SymbolTable& symbolTable) 
{
	boost::any value;
	value = symbolTable.getValue(compilerToken->getName());
	if (value.type() == typeid(ExceptionCodes)) {
		value = globalSymbolTable->getValue(compilerToken->getName());
		if (value.type() == typeid(ExceptionCodes)){
			throw exception();
		}
	}
	TokenType op = (compilerToken->getFrontOperator() != TokenType::Null) ? compilerToken->getFrontOperator() : compilerToken->getBackOperator();
	if (op != TokenType::Null) {
		double val = boost::any_cast<double>(value);
		bool isFrontOp = (compilerToken->getFrontOperator() != TokenType::Null);
		if (isFrontOp) {
			updateVariable(compilerToken->getName(), (op == TokenType::IncreaseOperator) ? ++val : --val, symbolTable);
			value = boost::any(val);
		}
		else{
			updateVariable(compilerToken->getName(), (op == TokenType::IncreaseOperator) ? ++val : --val, symbolTable);
		}
	}
	return value;
}

boost::any VirtualMachine::getReturnValue(ReturnValueCompilerToken* returnValueCompilerToken, SymbolTable& symbolTable)
{
	std::queue<boost::any> rpn = returnValueCompilerToken->getRPN();
	std::stack<boost::any> resultStack;
	while (!rpn.empty()) {
		boost::any value = rpn.front();
		rpn.pop();
		if (value.type() == typeid(TokenType)){
			TokenType op = boost::any_cast<TokenType>(value);
			boost::any right = resultStack.top();
			resultStack.pop();
			boost::any left = resultStack.top();
			resultStack.pop();
			if (exNumber(left,right,op,resultStack)){
				continue;
			}
			if (exString(left, right, op, resultStack)){
				continue;
			}
			if (exBool(left, right, op, resultStack)){
				continue;
			}
			throw exception();
		}
		else{
			if (value.type() == typeid(VarCompilerToken*))
				value = getVarValue(boost::any_cast<VarCompilerToken*>(value), symbolTable);
			else if (value.type() == typeid(FunctionCompilerToken*))
				value = executeAction(boost::any_cast<FunctionCompilerToken*>(value), symbolTable, currentAction);
			resultStack.push(value);
		}
	}
	return resultStack.top();
}

bool VirtualMachine::exString(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack)
{
	std::string lString;
	std::string rString;
	try{
		lString = boost::any_cast<std::string>(left);
		rString = boost::any_cast<std::string>(right);
	}
	catch(exception& e){
		return false;
	}
	switch (op){
	case TokenType::AddOperator:
		resultStack.push(lString + rString);
		break;
	case TokenType::IsStatement:
		resultStack.push(lString.compare(rString) == 0);
		break;
	case TokenType::NotStatement:
		resultStack.push(lString.compare(rString) != 0);
		break;
	default:
		throw exception();
		return false;
		break;
	}
	return true;
}

bool VirtualMachine::exNumber(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack)
{
	double lDouble;
	double rDouble;
	try{
		lDouble = boost::any_cast<double>(left);
		rDouble = boost::any_cast<double>(right);
	}
	catch (exception& e){
		return false;
	}
	switch (op){
	case TokenType::AddOperator:
		resultStack.push(lDouble + rDouble);
		break;
	case TokenType::MinusOperator:
		resultStack.push(lDouble - rDouble);
		break;
	case TokenType::MultiplyOperator:
		resultStack.push(lDouble * rDouble);
		break;
	case TokenType::DivideOperator:
		resultStack.push(lDouble / rDouble);
		break;
	case TokenType::ModuloOperator:
		resultStack.push((int)lDouble % (int)rDouble);
		break;
	case TokenType::IsStatement:
		resultStack.push(lDouble == rDouble);
		break;
	case TokenType::NotStatement:
		resultStack.push(lDouble != rDouble);
		break;
	case TokenType::GreatherOrEqualStatement:
		resultStack.push(lDouble >= rDouble);
		break;
	case TokenType::GreatherThenStatement:
		resultStack.push(lDouble > rDouble);
		break;
	case TokenType::LesserThenStatement:
		resultStack.push(lDouble < rDouble);
		break;
	case TokenType::LesserOrEqualStatement:
		resultStack.push(lDouble <= rDouble);
		break;
	default:
		throw exception();
		return false;
		break;
	}
	return true;
}

bool VirtualMachine::exBool(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack)
{
	bool lBool;
	bool rBool;
	try{
		lBool = boost::any_cast<bool>(left);
		rBool = boost::any_cast<bool>(right);
	}
	catch (exception& e){
		return false;
	}
	switch (op){
	case TokenType::IsStatement:
		resultStack.push(lBool == rBool);
		break;
	case TokenType::NotStatement:
		resultStack.push(lBool != rBool);
		break;
	case TokenType::OrStatement:
		if (lBool|| rBool){
			resultStack.push(true);
			break;
		}
		resultStack.push(false);
		break;
	case TokenType::AndStatement:
		resultStack.push(lBool && rBool);
		break;
	default:
		throw exception();
		return false;
		break;
	}
	return true;
}