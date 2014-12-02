#include "VirtualMachine.h"
#include "../Compiler/AssignCompilerToken.h"
#include "../Compiler/ConditionCompilerToken.h"
#include "../Compiler/FunctionCompilerToken.h"
#include "../Compiler/ReturnValueCompilerToken.h"
//#include "../Compiler/SubConditionCompilerToken.h"
#include "../Compiler/VarCompilerToken.h"
#include "../Compiler/ReturnCompilerToken.h"
#include <string>
#include "ExceptionCodes.h"

VirtualMachine::VirtualMachine()
{
}

VirtualMachine::VirtualMachine(SymbolTable* symbolTable)
{
	globalSymbolTable = symbolTable;
	currentSymbolTable = symbolTable;
}

VirtualMachine::~VirtualMachine()
{
}

void VirtualMachine::run(Action *firstAction)
{
	currentAction = firstAction;

	while (currentAction != nullptr)
	{
		
			//TODO: set the currentsymboltable from the information from the current action
			//TODO: donothingaction
			
			CompilerToken* compilerToken = currentAction->getCompilerToken();
			executeAction(compilerToken);

			//action = executeAction(action, action->getCompilerToken());

			//if (compilerToken == nullptr) //this is DoNothingAction
			//{
			//	currentAction = currentAction->getNextAction();
			//}
			//else if (typeid(*compilerToken) == typeid(AssignCompilerToken))
			//{
			//	executeAction((AssignCompilerToken*)compilerToken);
			//}
			//else if (typeid(*compilerToken) == typeid(FunctionCompilerToken)) {
			//	executeAction((FunctionCompilerToken*)compilerToken);
			//}
		
	}
}

void VirtualMachine::addVariable(std::string name, boost::any value) {
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
		// Think of a better way to do this
		if (typeid(*ct) == typeid(ReturnValueCompilerToken))
			executeAction((ReturnValueCompilerToken*)ct);
		else if (typeid(*ct) == typeid(AssignCompilerToken))
			executeAction((AssignCompilerToken*)ct);
		else if (typeid(*ct) == typeid(FunctionCompilerToken))
			executeAction((FunctionCompilerToken*)ct);
		else if (typeid(*ct) == typeid(ConditionCompilerToken))
			executeAction((ConditionCompilerToken*)ct);
		/*else if (typeid(*ct) == typeid(SubConditionCompilerToken))
			executeAction((SubConditionCompilerToken*)ct);*/
		else if (typeid(*ct) == typeid(VarCompilerToken))
			executeAction((VarCompilerToken*)ct);
		else
			currentAction = currentAction->getNextAction();
	}
}

void VirtualMachine::executeAction(ReturnValueCompilerToken* compilerToken) {
	getReturnValue(compilerToken);
	currentAction = currentAction->getNextAction();
}

void VirtualMachine::executeAction(AssignCompilerToken* compilerToken)
{
	//TODO: -=, +=, etc...
	// Do this by setting another var in compilerToken which holds the operator type
	// Apply an extra calculation based on the operator
	boost::any val = getVarValue(&VarCompilerToken(compilerToken->getName()));/*currentSymbolTable->getValue(compilerToken->getName());*/
	boost::any newVal = getReturnValue(compilerToken->getReturnValue());

	switch (compilerToken->getAssignOp()) {
		case TokenType::AssignmentOperator: val = newVal; break;
		case TokenType::AddThenAssignOperator: 
		{ 
			if (val.type() == typeid(std::string))
				val = boost::any_cast<std::string>(val) + boost::any_cast<std::string>(newVal);
			else
				val = boost::any_cast<double>(val) + boost::any_cast<double>(newVal);
			break;
		}
		case TokenType::MinusThenAssignOperator: val = boost::any_cast<double>(val) - boost::any_cast<double>(newVal); break;
		case TokenType::DivideThenAssignOperator: val = boost::any_cast<double>(val) / boost::any_cast<double>(newVal); break;
		case TokenType::MultiplyThenAssignOperator: val = boost::any_cast<double>(val) * boost::any_cast<double>(newVal); break;
	}

	updateVariable(compilerToken->getName(), val);

	currentAction = currentAction->getNextAction();
	//return action->getNextAction();
}

void VirtualMachine::executeAction(FunctionCompilerToken* compilerToken)
{
	//TODO: if the function has a return type, do not forget to set the result
	getFunctionValue(compilerToken);
	
}

void VirtualMachine::executeAction(ConditionCompilerToken* compilerToken)
{
	//TODO: write this method
	//return nullptr;
	currentAction = (boost::any_cast<bool>(getReturnValue(compilerToken->getReturnValueCompilerToken()))) ? currentAction->getNextAction() : currentAction->getFalseAction();
}

//void VirtualMachine::executeAction(SubConditionCompilerToken* compilerToken)
//{
//	//TODO: write this method
//	//return nullptr;
//}

void VirtualMachine::executeAction(VarCompilerToken* compilerToken)
{
	// TODO: Clean all commented code
	//TODO: use the correct symboltable with the corrosponding action
	//boost::any value = currentSymbolTable->getValue(compilerToken->getName());
	getVarValue(compilerToken);

	// Old getVar function

	//TokenType frontOperator = compilerToken->getFrontOperator();
	//TokenType backOperator = compilerToken->getBackOperator();

	//if (frontOperator != TokenType::Null)
	//{
	//	if (frontOperator == TokenType::IncreaseOperator)
	//	{
	//		if (value.type() == typeid(double))
	//		{
	//			double result = boost::any_cast<double>(value);
	//			result++;
	//			updateVariable(compilerToken->getName(), result);
	//			compilerToken->setResult(result);
	//		}
	//		else
	//		{
	//			throw new exception; //You can only do increase on a number. TODO: better exception handling
	//		}
	//	}
	//	else if (frontOperator == TokenType::DecreaseOperator)
	//	{
	//		if (value.type() == typeid(double))
	//		{
	//			double result = boost::any_cast<double>(value);
	//			result--;
	//			updateVariable(compilerToken->getName(), result);
	//			compilerToken->setResult(result);
	//		}
	//		else
	//		{
	//			throw new exception; //You can only do decrease on a number. TODO: better exception handling
	//		}
	//	}
	//}
	//else if (backOperator != TokenType::Null)
	//{
	//	if (backOperator == TokenType::IncreaseOperator)
	//	{
	//		if (value.type() == typeid(double))
	//		{
	//			double result = boost::any_cast<double>(value);
	//			compilerToken->setResult(result);
	//			result++;
	//			updateVariable(compilerToken->getName(), result);
	//		}
	//		else
	//		{
	//			throw new exception; //You can only do increase on a number. TODO: better exception handling
	//		}
	//	}
	//	else if (backOperator == TokenType::DecreaseOperator)
	//	{
	//		if (value.type() == typeid(double))
	//		{
	//			double result = boost::any_cast<double>(value);
	//			compilerToken->setResult(result);
	//			result--;
	//			updateVariable(compilerToken->getName(), result);
	//		}
	//		else
	//		{
	//			throw new exception; //You can only do decrease on a number. TODO: better exception handling
	//		}
	//	}
	//}
	//else
	//{
	//	compilerToken->setResult(value);
	//}
	if (currentAction->getNextAction() != nullptr)
		currentAction = currentAction->getNextAction();
}

boost::any VirtualMachine::getVarValue(VarCompilerToken* compilerToken) {
	// TODO: test method
	boost::any value;
	// nasty code needs better solution, no exception thrown in symboltable but here
	value = currentSymbolTable->getValue(compilerToken->getName());
	if (value.type() == typeid(ExceptionCodes)) {
		value = globalSymbolTable->getValue(compilerToken->getName());
		if (value.type() == typeid(ExceptionCodes))
			throw exception(); // TODO: check exceptioncode value and give proper exception
	}
	TokenType op = (compilerToken->getFrontOperator() != TokenType::Null) ? compilerToken->getFrontOperator() : compilerToken->getBackOperator();

	if (op != TokenType::Null) {
		//if (std::isnan(value)) 
		//	// Not a Number exception
		//	throw exception(); // TODO: better exception

		double val = boost::any_cast<double>(value);
		bool isFrontOp = (compilerToken->getFrontOperator() != TokenType::Null);
		if (isFrontOp) {
			updateVariable(compilerToken->getName(), (op == TokenType::IncreaseOperator) ? ++val : --val);
			value = boost::any(val);
		} else
			updateVariable(compilerToken->getName(), (op == TokenType::IncreaseOperator) ? ++val : --val );
	}

	return value;
}

boost::any VirtualMachine::getFunctionValue(FunctionCompilerToken* compilerToken) {
	// TODO: Get vars from global symboltable and function symboltable
	FunctionSymbol* fs = currentSymbolTable->getFunctionSymbol(compilerToken->getName(), compilerToken->getArguments().size());
	if (fs == nullptr) {
		currentAction = currentAction->getNextAction();
		// throw exception(); Function not found
		return nullptr;
	}
	if (fs->isInternal()) {
		IInternalFunction* fnc = InternalFunctionFactory::Instance()->Create(fs->getName());
		std::vector<boost::any> args;
		for each(ReturnValueCompilerToken* rvct in compilerToken->getArguments()) {
			args.push_back(getReturnValue(rvct));
		}
		fnc->Execute(args); 

		currentAction = currentAction->getNextAction();
		return fnc->GetResult();
	}
	else {
		FunctionCompilerToken* fct = (FunctionCompilerToken*)fs->getStartAction()->getCompilerToken();
		std::vector<std::string> argNames = fct->getArgumentNames();
		for (int i = 0; i < argNames.size(); i++) {
			// TODO: Add variable to function symboltable
			addVariable(argNames[i], getReturnValue(compilerToken->getArguments()[i]));
		}
		currentAction = fs->getStartAction()->getNextAction();
		boost::any returnValue = nullptr;
		while (currentAction != fs->getEndAction()) {
			if (typeid(currentAction->getCompilerToken()) == typeid(ReturnCompilerToken)) {
				returnValue = getReturnValue(((ReturnCompilerToken*)currentAction->getCompilerToken())->getReturnValueCompilerToken());
				break;
			} else
				executeAction(currentAction->getCompilerToken());
		}
		currentAction = fs->getEndAction();
		return returnValue;
		// TODO: remove vars from function
	}
	// Temp return
	return nullptr;
}

boost::any VirtualMachine::getReturnValue(ReturnValueCompilerToken* returnValueCompilerToken)
{
	//TODO: check and clean this method
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
				value = getFunctionValue(boost::any_cast<FunctionCompilerToken*>(left));
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

void VirtualMachine::print(boost::any p)
{
	std::string r;
	try {
		r = std::to_string(boost::any_cast<double>(p));
	}
	catch (exception e) {
		r = boost::any_cast<std::string>(p);
	}
	std::cout << r << endl;
}