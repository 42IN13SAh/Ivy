#include <string>
#include "InternalFunctionFactory.h"
#include "ExceptionCodes.h"
#include "VirtualMachine.h"
#include "Cast.h"
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
		boost::shared_ptr<CompilerToken> compilerToken = currentAction->getCompilerToken();
		executeAction(compilerToken, *globalSymbolTable);
	}
}

void VirtualMachine::addVariable(std::string name, boost::any value, SymbolTable& symbolTable) 
{
	symbolTable.addSymbolToTable(name, value);
}

void VirtualMachine::updateVariable(std::string name, boost::any value, SymbolTable& symbolTable)
{
	if (symbolTable.hasSymbol(name)){
		symbolTable.updateExistingSymbol(name, value);
	}
	else{
		globalSymbolTable->updateExistingSymbol(name, value);
	}
}

void VirtualMachine::executeAction(boost::shared_ptr<CompilerToken> ct, SymbolTable& symbolTable){
	if (ct != nullptr){
		if (boost::dynamic_pointer_cast<ReturnValueCompilerToken>(ct) != NULL){
			executeAction(boost::dynamic_pointer_cast<ReturnValueCompilerToken>(ct), symbolTable);
			currentAction = currentAction->getNextAction();
		}
		else if (boost::dynamic_pointer_cast<AssignCompilerToken>(ct) != NULL){
			executeAction(boost::dynamic_pointer_cast<AssignCompilerToken>(ct), symbolTable);
			currentAction = currentAction->getNextAction();
		}
		else if (boost::dynamic_pointer_cast<FunctionCompilerToken>(ct) != NULL){
			executeAction(boost::dynamic_pointer_cast<FunctionCompilerToken>(ct), symbolTable, currentAction);
		}
		else if (boost::dynamic_pointer_cast<ConditionCompilerToken>(ct) != NULL){
			if (executeAction(boost::dynamic_pointer_cast<ConditionCompilerToken>(ct), symbolTable)){
				currentAction = currentAction->getNextAction();
			}
			else{
				currentAction = currentAction->getFalseAction();
			}
		}
		else if (boost::dynamic_pointer_cast<VarCompilerToken>(ct) != NULL){
			executeAction(boost::dynamic_pointer_cast<VarCompilerToken>(ct), symbolTable);
			currentAction = currentAction->getNextAction();
		}
	}
	else{
		currentAction = currentAction->getNextAction();
	}
}

void VirtualMachine::executeAction(boost::shared_ptr<ReturnValueCompilerToken> compilerToken, SymbolTable& symbolTable) {
	getReturnValue(compilerToken, symbolTable);
}

void VirtualMachine::executeAction(boost::shared_ptr<AssignCompilerToken> compilerToken, SymbolTable& symbolTable)
{
	boost::any val = getVarValue(boost::shared_ptr<VarCompilerToken>(new VarCompilerToken(compilerToken->getName())), symbolTable);
	boost::any newVal = getReturnValue(compilerToken->getReturnValue(), symbolTable);
	switch (compilerToken->getAssignOp()) {
	case TokenType::AssignmentOperator: val = newVal; break;
	case TokenType::AddThenAssignOperator:
	{
											 if (val.type() == typeid(std::string)){
												 val = Cast::cast<std::string>(val)+Cast::cast<std::string>(newVal);
											 }
											 else{
												 val = Cast::cast<double>(val)+Cast::cast<double>(newVal);
											 }
											 break;
	}
	case TokenType::MinusThenAssignOperator:
		val = Cast::cast<double>(val)-Cast::cast<double>(newVal);
		break;
	case TokenType::DivideThenAssignOperator:
		if (Cast::cast<double>(newVal) == 0) throw DivideByZeroException();
		val = Cast::cast<double>(val) / Cast::cast<double>(newVal);
		break;
	case TokenType::MultiplyThenAssignOperator:
		val = Cast::cast<double>(val)* Cast::cast<double>(newVal);
		break;
	}
	updateVariable(compilerToken->getName(), val, symbolTable);
}

boost::any VirtualMachine::executeAction(boost::shared_ptr<FunctionCompilerToken> compilerToken, SymbolTable& symbolTable, Action* fAction)
{
	FunctionSymbol* fs = globalSymbolTable->getFunctionSymbol(compilerToken->getName(), compilerToken->getArguments().size());
	if (fs->isInternal()){
		return executeInternalFunction(fs->getName(), compilerToken, symbolTable);
	}
	else{
		boost::shared_ptr<FunctionCompilerToken> fct = boost::dynamic_pointer_cast<FunctionCompilerToken>(fs->getStartAction()->getCompilerToken());
		currentAction = fs->getStartAction()->getNextAction();
		std::vector<std::string> argNames = fct->getArgumentNames();
		for (int i = 0; i < argNames.size(); i++) {
			fs->getSymbolTable()->updateExistingSymbol(argNames[i], getReturnValue(boost::dynamic_pointer_cast<ReturnValueCompilerToken>(compilerToken->getArguments()[i]), symbolTable));
		}
		boost::any returnValue = nullptr;
		while (currentAction != fs->getEndAction()){
			if (currentAction->getCompilerToken() != nullptr  && (boost::dynamic_pointer_cast<ReturnCompilerToken>(currentAction->getCompilerToken()) != NULL)) {
				boost::shared_ptr<ReturnCompilerToken> rct = boost::dynamic_pointer_cast<ReturnCompilerToken>(currentAction->getCompilerToken());
				returnValue = getReturnValue(rct->getReturnValueCompilerToken(), *fs->getSymbolTable());
				break;
			}
			else{
				executeAction(currentAction->getCompilerToken(), *fs->getSymbolTable());
			}
		}
		currentAction = fAction->getNextAction();
		fs->getSymbolTable()->clearSymbolTable();
		return returnValue;
	}
	return nullptr;
}

boost::any VirtualMachine::executeInternalFunction(std::string name, boost::shared_ptr<FunctionCompilerToken> compilerToken, SymbolTable& symbolTable){
	IInternalFunction* fnc = InternalFunctionFactory::Instance()->Create(name);
	std::vector<boost::any> args;
	for each(boost::shared_ptr<ReturnValueCompilerToken> rvct in compilerToken->getArguments()) {
		args.push_back(getReturnValue(rvct, symbolTable));
	}
	if (currentAction->getNextAction() != NULL){
		currentAction = currentAction->getNextAction();
	}
	fnc->Execute(args);
	return fnc->GetResult();
}

bool VirtualMachine::executeAction(boost::shared_ptr<ConditionCompilerToken> compilerToken, SymbolTable& symbolTable)
{
	return (Cast::cast<bool>(getReturnValue(compilerToken->getReturnValueCompilerToken(), symbolTable)));
}

void VirtualMachine::executeAction(boost::shared_ptr<VarCompilerToken> compilerToken, SymbolTable& symbolTable)
{
	getVarValue(compilerToken, symbolTable);
}

boost::any VirtualMachine::getVarValue(boost::shared_ptr<VarCompilerToken> compilerToken, SymbolTable& symbolTable) 
{
	boost::any value;
	value = symbolTable.getValue(compilerToken->getName());
	if (value.type() == typeid(ExceptionCodes)) {
		value = globalSymbolTable->getValue(compilerToken->getName());
		if (value.type() == typeid(ExceptionCodes)){
			if (boost::any_cast<ExceptionCodes>(value) == ExceptionCodes::VarNotFound)
				throw VariableNotFoundException(compilerToken->getName());
		}
	}
	TokenType::TokenType op = (compilerToken->getFrontOperator() != TokenType::Null) ? compilerToken->getFrontOperator() : compilerToken->getBackOperator();
	if (op != TokenType::Null) {
		double val = Cast::cast<double>(value);
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

boost::any VirtualMachine::getReturnValue(boost::shared_ptr<ReturnValueCompilerToken> returnValueCompilerToken, SymbolTable& symbolTable)
{
	Action* tempAction = currentAction;
	std::queue<boost::any> rpn = returnValueCompilerToken->getRPN();
	std::stack<boost::any> resultStack;
	while (!rpn.empty()) {
		boost::any value = rpn.front();
		rpn.pop();
		if (value.type() == typeid(TokenType::TokenType)){
			TokenType::TokenType op = Cast::cast<TokenType::TokenType>(value);
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
			if (exStringNumber(left, right, op, resultStack)){
				continue;
			}
			if (exNumberString(left, right, op, resultStack)){
				continue;
			}
			if (exBool(left, right, op, resultStack)){
				continue;
			}
			throw TypeMismatchException(TokenType::TokenTypeNames[op], left.type().name(), right.type().name()); // Invalid value type
		}
		else{
			if (value.type() == typeid(boost::shared_ptr<VarCompilerToken>)){
				value = getVarValue(boost::any_cast<boost::shared_ptr<VarCompilerToken>>(value), symbolTable);
			}
			else if (value.type() == typeid(boost::shared_ptr<FunctionCompilerToken>)){
				value = executeAction(boost::any_cast<boost::shared_ptr<FunctionCompilerToken>>(value), symbolTable, currentAction);
				currentAction = tempAction;
			}
			resultStack.push(value);
		}
	}
	if (resultStack.empty()) throw EmptyResultStackException();
	return resultStack.top();
}

bool VirtualMachine::exString(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack)
{
	std::string lString;
	std::string rString;
	try{
		lString = boost::any_cast<std::string>(left);
		rString = boost::any_cast<std::string>(right);
	}
	catch (std::exception& e){
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
		throw UnexpectedOperatorException(TokenType::TokenTypeNames[op], "String");
		return false;
	}
	return true;
}

bool VirtualMachine::exNumber(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack)
{
	double lDouble;
	double rDouble;
	try{
		lDouble = boost::any_cast<double>(left);
		rDouble = boost::any_cast<double>(right);
	}
	catch (std::exception& e){
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
		if (rDouble == 0) throw DivideByZeroException();
		resultStack.push(lDouble / rDouble);
		break;
	case TokenType::ModuloOperator:
		resultStack.push((double)((int)lDouble % (int)rDouble));
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
		throw UnexpectedOperatorException(TokenType::TokenTypeNames[op], "Double");
		return false;
	}
	return true;
}

bool VirtualMachine::exBool(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack)
{
	bool lBool;
	bool rBool;
	try{
		lBool = Cast::cast<bool>(left);
		rBool = Cast::cast<bool>(right);
	}
	catch (std::exception& e){
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
		throw UnexpectedOperatorException(TokenType::TokenTypeNames[op], "Boolean");
		return false;
	}
	return true;
}

bool VirtualMachine::exStringNumber(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack){
	std::string lString;
	double rNumber;
	try{
		lString = Cast::cast<std::string>(left);
		rNumber = Cast::cast<double>(right);
	}
	catch (std::exception& e){
		return false;
	}
	switch (op){
	case TokenType::AddOperator:
		resultStack.push(lString + std::to_string(rNumber));
		break;
	default:
		throw UnexpectedOperatorException(TokenType::TokenTypeNames[op], "String", "Double");
		return false;
	}
	return true;
}

bool VirtualMachine::exNumberString(boost::any left, boost::any right, TokenType::TokenType op, std::stack<boost::any>& resultStack){
	double lNumber;
	std::string rString;
	try{
		lNumber = Cast::cast<double>(left);
		rString = Cast::cast<std::string>(right);
	}
	catch (std::exception& e){
		return false;
	}
	switch (op){
	case TokenType::AddOperator:
		resultStack.push(std::to_string(lNumber) + rString);
		break;
	default:
		throw UnexpectedOperatorException(TokenType::TokenTypeNames[op], "Double", "String");
		return false;
	}
	return true;
}