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
	this->currentSymbolTable = globalSymbolTable;
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
		executeAction(compilerToken);
	}
}

void VirtualMachine::addVariable(std::string name, boost::any value) 
{
	currentSymbolTable->addSymbolToTable(name, value);
}

void VirtualMachine::updateVariable(string name, boost::any value)
{
	currentSymbolTable->updateExistingSymbol(name, value);
}

void VirtualMachine::executeAction(CompilerToken* ct){ 
	if (ct == nullptr){
		currentAction = currentAction->getNextAction();
	}
	else{
		if (typeid(*ct) == typeid(ReturnValueCompilerToken)){
			executeAction((ReturnValueCompilerToken*)ct);
		}
		else if (typeid(*ct) == typeid(AssignCompilerToken)){
			executeAction((AssignCompilerToken*)ct);
		}
		else if (typeid(*ct) == typeid(FunctionCompilerToken)){
			executeAction((FunctionCompilerToken*)ct, currentAction);
		}
		else if (typeid(*ct) == typeid(ConditionCompilerToken)){
			executeAction((ConditionCompilerToken*)ct);
		}
		else if (typeid(*ct) == typeid(VarCompilerToken)){
			executeAction((VarCompilerToken*)ct);
		}
		else{
			currentAction = currentAction->getNextAction();
		}
	}
}

void VirtualMachine::executeAction(ReturnValueCompilerToken* compilerToken) {
	getReturnValue(compilerToken);
	currentAction = currentAction->getNextAction();
}

void VirtualMachine::executeAction(AssignCompilerToken* compilerToken)
{
	boost::any val = getVarValue(&VarCompilerToken(compilerToken->getName()));
	boost::any newVal = getReturnValue(compilerToken->getReturnValue());
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
			val = boost::any_cast<double>(val) - boost::any_cast<double>(newVal); 
			break;
		case TokenType::DivideThenAssignOperator: 
			val = boost::any_cast<double>(val) / boost::any_cast<double>(newVal); 
			break;
		case TokenType::MultiplyThenAssignOperator: 
			val = boost::any_cast<double>(val) * boost::any_cast<double>(newVal); 
			break;
	}
	updateVariable(compilerToken->getName(), val);
	currentAction = currentAction->getNextAction();
}

void VirtualMachine::executeAction(FunctionCompilerToken* compilerToken, Action* lastAction)
{
	getFunctionValue(compilerToken, lastAction);
}

void VirtualMachine::executeAction(ConditionCompilerToken* compilerToken)
{
	currentAction = (boost::any_cast<bool>(getReturnValue(compilerToken->getReturnValueCompilerToken()))) ? currentAction->getNextAction() : currentAction->getFalseAction();
}

void VirtualMachine::executeAction(VarCompilerToken* compilerToken)
{
	getVarValue(compilerToken);
	if (currentAction->getNextAction() != nullptr){
		currentAction = currentAction->getNextAction();
	}
}

boost::any VirtualMachine::getVarValue(VarCompilerToken* compilerToken) 
{
	boost::any value;
	value = currentSymbolTable->getValue(compilerToken->getName());
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
			updateVariable(compilerToken->getName(), (op == TokenType::IncreaseOperator) ? ++val : --val);
			value = boost::any(val);
		}
		else{
			updateVariable(compilerToken->getName(), (op == TokenType::IncreaseOperator) ? ++val : --val);
		}
	}
	return value;
}

boost::any VirtualMachine::getFunctionValue(FunctionCompilerToken* compilerToken, Action* lastAction) 
{
	FunctionSymbol* fs = currentSymbolTable->getFunctionSymbol(compilerToken->getName(), compilerToken->getArguments().size());
	if (fs->isInternal()){
		IInternalFunction* fnc = InternalFunctionFactory::Instance()->Create(fs->getName());
		std::vector<boost::any> args;
		for each(ReturnValueCompilerToken* rvct in compilerToken->getArguments()) {
			args.push_back(getReturnValue(rvct));
		}
		fnc->Execute(args);
		currentAction = currentAction->getNextAction();
		return fnc->GetResult();
	}
	else{
		FunctionCompilerToken* fct = (FunctionCompilerToken*)fs->getStartAction()->getCompilerToken();
		std::vector<std::string> argNames = fct->getArgumentNames();
		for (int i = 0; i < argNames.size(); i++) {
			fs->getSymbolTable()->addSymbolToTable(argNames[i], getReturnValue(compilerToken->getArguments()[i]));
		}
		currentAction = fs->getStartAction()->getNextAction();
		boost::any returnValue = nullptr;
		while (currentAction != fs->getEndAction()) {
			if (typeid(currentAction->getCompilerToken()) == typeid(ReturnCompilerToken)) {
				returnValue = getReturnValue(((ReturnCompilerToken*)currentAction->getCompilerToken())->getReturnValueCompilerToken());
				break;
			}
			else
				executeAction(currentAction->getCompilerToken());
		}
		if (currentAction != lastAction->getNextAction()){
			currentAction = lastAction->getNextAction();
		}
		return returnValue;
	}
	return nullptr;
}

boost::any VirtualMachine::getReturnValue(ReturnValueCompilerToken* returnValueCompilerToken)
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
				value = getVarValue(boost::any_cast<VarCompilerToken*>(value));
			else if (value.type() == typeid(FunctionCompilerToken*))
				value = getFunctionValue(boost::any_cast<FunctionCompilerToken*>(left), currentAction);
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