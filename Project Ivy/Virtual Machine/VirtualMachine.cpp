#include "VirtualMachine.h"
#include "../Compiler/AssignCompilerToken.h"
#include "../Compiler/ConditionCompilerToken.h"
#include "../Compiler/FunctionCompilerToken.h"
#include "../Compiler/ReturnValueCompilerToken.h"
//#include "../Compiler/SubConditionCompilerToken.h"
#include "../Compiler/VarCompilerToken.h"
#include "../Compiler/ReturnCompilerToken.h"
#include <string>

VirtualMachine::VirtualMachine()
{
}

VirtualMachine::VirtualMachine(SymbolTable* symbolTable)
{
	this->currentSymbolTable = symbolTable;
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
			if (compilerToken != nullptr)
				executeAction(compilerToken);
			else
				currentAction = currentAction->getNextAction();

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

void VirtualMachine::executeAction(ReturnValueCompilerToken* compilerToken) {
	getReturnValue(compilerToken);
	currentAction = currentAction->getNextAction();
}

void VirtualMachine::executeAction(AssignCompilerToken* compilerToken)
{
	//TODO: -=, +=, etc...
	// Do this by setting another var in compilerToken which holds the operator type
	// Apply an extra calculation based on the operator
	boost::any val = currentSymbolTable->getValue(compilerToken->getName());
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
	boost::any value = currentSymbolTable->getValue(compilerToken->getName());
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
			updateVariable(compilerToken->getName(), (op == TokenType::IncreaseOperator) ? val++ : val-- );
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
		// TODO: get function from internal function list, parse arguments and execute
		if (fs->getName() == "print") {
			print(getReturnValue(compilerToken->getArguments()[0]));
		}

		/*std::shared_ptr<IInternalFunction> fnc = InternalFunctionFactory::Instance()->Create(fs->getName());
		std::vector<boost::any> args;
		for each(ReturnValueCompilerToken* rvct in compilerToken->getArguments()) {
			args.push_back(getReturnValue(rvct));
		}
		fnc->Execute(args); */

		currentAction = currentAction->getNextAction();
		/*return fnc->GetResult();*/
		// TODO: Return returnvalue from function
	}
	else {
		FunctionCompilerToken* fct = (FunctionCompilerToken*)fs->getStartAction()->getCompilerToken();
		std::vector<std::string> argNames = fct->getArgumentNames();
		for (int i = 0; i < argNames.size(); i++) {
			// TODO: Add variable to function symboltable
			addVariable(argNames[i], getReturnValue(compilerToken->getArguments()[i]));
		}
		Action* ca = fs->getStartAction();
		boost::any returnValue = nullptr;
		while (ca != fs->getEndAction()) {
			if (typeid(ca->getCompilerToken()) == typeid(ReturnCompilerToken)) {
				returnValue = getReturnValue(((ReturnCompilerToken*)ca->getCompilerToken())->getReturnValueCompilerToken());
				break;
			} else
				executeAction(ca->getCompilerToken());
			// TODO: if compilerToken == returncompilertoken set value as return value
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

	while (rpn.size() != 1) {
		boost::any left = rpn.front();
		rpn.pop();
		boost::any right = rpn.front();
		rpn.pop();

		if (left.type() == typeid(VarCompilerToken*))
			left = getVarValue(boost::any_cast<VarCompilerToken*>(left));
		else if (left.type() == typeid(FunctionCompilerToken*))
			left = getFunctionValue(boost::any_cast<FunctionCompilerToken*>(left));

		if (right.type() == typeid(VarCompilerToken*))
			right = getVarValue(boost::any_cast<VarCompilerToken*>(right));
		else if (right.type() == typeid(FunctionCompilerToken*))
			right = getFunctionValue(boost::any_cast<FunctionCompilerToken*>(right));

		TokenType op = boost::any_cast<TokenType>(rpn.front());
		rpn.pop();

		try{
			left = stod(boost::any_cast<std::string>(left));
			right = stod(boost::any_cast<std::string>(right));
		} catch (exception e) {}

		if (left.type() == typeid(std::string) || right.type() == typeid(std::string)) {
			std::string l = (left.type() == typeid(std::string)) ? boost::any_cast<std::string>(left) : std::to_string(boost::any_cast<double>(left));
			std::string r = (right.type() == typeid(std::string)) ? boost::any_cast<std::string>(right) : std::to_string(boost::any_cast<double>(right));
			if (op == TokenType::AddOperator)
				rpn.push(l + r);
			else
				// cannot use this operator on strings
				throw exception(); // TODO: Better exception
		}
		else /* if (isdigit(left) && isdigit(right)) */ {
			double l = boost::any_cast<double>(left);
			double r = boost::any_cast<double>(right);
			switch (op) {
				case TokenType::AddOperator: rpn.push(l + r); break;
				case TokenType::MinusOperator: rpn.push(l - r); break;
				case TokenType::DivideOperator: rpn.push(l / r); break;
				case TokenType::MultiplyOperator: rpn.push(l * r); break;
				case TokenType::ModuloOperator: rpn.push((int)l % (int)r); break;
			}
		}
	}

	return rpn.front();

	// Old RPN function

	//for (size_t i = 0; i < rpnVector.size(); i++)
	//{
	//	boost::any value = nullptr;

	//	if (value.type() == typeid(string))
	//	{
	//		resultStack.push(atof(boost::any_cast<string>(value).c_str()));
	//	}
	//	else if (value.type() == typeid(TokenType))
	//	{
	//		double b = boost::any_cast<double>(resultStack.top());
	//		resultStack.pop();
	//		double a = boost::any_cast<double>(resultStack.top());
	//		resultStack.pop();

	//		switch (boost::any_cast<TokenType>(value))
	//		{
	//		case TokenType::AddOperator:
	//			resultStack.push(a + b);
	//			break;
	//		case TokenType::MinusOperator:
	//			resultStack.push(a - b);
	//			break;
	//		case TokenType::DivideOperator:
	//			resultStack.push(a / b);
	//			break;
	//		case TokenType::MultiplyOperator:
	//			resultStack.push(a * b);
	//			break;
	//		case TokenType::ModuloOperator:
	//			resultStack.push((int)a % (int)b);
	//			break;
	//		}
	//	}
	//	else if (value.type() == typeid(VarCompilerToken*))
	//	{
	//		VarCompilerToken* varCompilerToken = boost::any_cast<VarCompilerToken*>(value);

	//		//executeAction(varCompilerToken);

	//		//resultStack.push(varCompilerToken->getResult());
	//		resultStack.push(getVarValue(varCompilerToken));
	//	}
	//	else //it is a function
	//	{
	//		FunctionCompilerToken* functionCompilerToken = boost::any_cast<FunctionCompilerToken*>(value);

	//		executeAction(functionCompilerToken);

	//		resultStack.push(functionCompilerToken->getResult());
	//	}
	//}

	//return resultStack.top();
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