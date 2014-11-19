#include "VirtualMachine.h"
#include "../Compiler/AssignCompilerToken.h"
#include "../Compiler/ConditionCompilerToken.h"
#include "../Compiler/FunctionCompilerToken.h"
#include "../Compiler/ReturnValueCompilerToken.h"
#include "../Compiler/SubConditionCompilerToken.h"
#include "../Compiler/VarCompilerToken.h"
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
				executeAction(compilerToken->Get());
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

void VirtualMachine::executeAction(CompilerToken* ct){ currentAction = currentAction->getNextAction(); }

void VirtualMachine::executeAction(ReturnValueCompilerToken* compilerToken) {
	getReturnValue(compilerToken);
	currentAction = currentAction->getNextAction();
}

void VirtualMachine::executeAction(AssignCompilerToken* compilerToken)
{
	//TODO: -=, +=, etc...
	
	updateVariable(compilerToken->getName(), getReturnValue(compilerToken->getReturnValue()));

	currentAction = currentAction->getNextAction();
	//return action->getNextAction();
}

void VirtualMachine::executeAction(FunctionCompilerToken* compilerToken)
{
	//TODO: if the function has a return type, do not forget to set the result
	FunctionSymbol* fs = currentSymbolTable->getFunctionSymbol(compilerToken->getName(), compilerToken->getArguments().size());
	if (fs->isInternal()) {
		// TODO: get function from internal function list, parse arguments and execute
		if (fs->getName() == "print") {
			print(getReturnValue(compilerToken->getArguments()[0]));
		}

		currentAction = currentAction->getNextAction();
	} else {
		FunctionCompilerToken* fct = (FunctionCompilerToken*)fs->getStartAction()->getCompilerToken();
		std::vector<std::string> argNames = fct->getArgumentNames();
		for (int i = 0; i < argNames.size(); i++) {
			addVariable(argNames[i], getReturnValue(compilerToken->getArguments()[i]));
		}
		Action* ca = fs->getStartAction();
		while (ca != fs->getEndAction()) {
			executeAction(ca->getCompilerToken());
		}

		currentAction = fs->getEndAction();

		// TODO: remove vars from function
	}
}

void VirtualMachine::executeAction(ConditionCompilerToken* compilerToken)
{
	//TODO: write this method
	//return nullptr;
}

void VirtualMachine::executeAction(SubConditionCompilerToken* compilerToken)
{
	//TODO: write this method
	//return nullptr;
}

void VirtualMachine::executeAction(VarCompilerToken* compilerToken)
{
	// TODO: Clean all commented code
	//TODO: use the correct symboltable with the corrosponding action
	//boost::any value = currentSymbolTable->getValue(compilerToken->getName());
	getVarValue(compilerToken);

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

boost::any VirtualMachine::getReturnValue(ReturnValueCompilerToken* returnValueCompilerToken)
{
	//TODO: check and clean this method
	std::stack<boost::any> resultStack;
	vector<boost::any>* rpnVector = returnValueCompilerToken->getrpnVector();

	for (size_t i = 0; i < rpnVector->size(); i++)
	{
		boost::any value = rpnVector->at(i);

		if (value.type() == typeid(string))
		{
			resultStack.push(atof(boost::any_cast<string>(value).c_str()));
		}
		else if (value.type() == typeid(TokenType))
		{
			double b = boost::any_cast<double>(resultStack.top());
			resultStack.pop();
			double a = boost::any_cast<double>(resultStack.top());
			resultStack.pop();

			switch (boost::any_cast<TokenType>(value))
			{
			case TokenType::AddOperator:
				resultStack.push(a + b);
				break;
			case TokenType::MinusOperator:
				resultStack.push(a - b);
				break;
			case TokenType::DivideOperator:
				resultStack.push(a / b);
				break;
			case TokenType::MultiplyOperator:
				resultStack.push(a * b);
				break;
			case TokenType::ModuloOperator:
				resultStack.push((int)a % (int)b);
				break;
			}
		}
		else if (value.type() == typeid(VarCompilerToken*))
		{
			VarCompilerToken* varCompilerToken = boost::any_cast<VarCompilerToken*>(value);

			//executeAction(varCompilerToken);

			//resultStack.push(varCompilerToken->getResult());
			resultStack.push(getVarValue(varCompilerToken));
		}
		else //it is a function
		{
			FunctionCompilerToken* functionCompilerToken = boost::any_cast<FunctionCompilerToken*>(value);

			executeAction(functionCompilerToken);

			resultStack.push(functionCompilerToken->getResult());
		}
	}

	return resultStack.top();
}



void VirtualMachine::print(boost::any p)
{
	std::cout << std::to_string(boost::any_cast<double>(p)) << endl;
}