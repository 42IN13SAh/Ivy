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
			//action = executeAction(action, action->getCompilerToken());

			if (compilerToken == nullptr) //this is DoNothingAction
			{
				currentAction = currentAction->getNextAction();
			}
			else if (typeid(*compilerToken) == typeid(AssignCompilerToken))
			{
				executeAction((AssignCompilerToken*)compilerToken);
			}
			else if (typeid(*compilerToken) == typeid(FunctionCompilerToken)) {
				executeAction((FunctionCompilerToken*)compilerToken);
			}
		
	}
}


void VirtualMachine::updateVariable(string name, boost::any value)
{
	currentSymbolTable->updateExistingSymbol(name, value);
}

void VirtualMachine::executeAction(CompilerToken* ct){ currentAction = currentAction->getNextAction(); }

void VirtualMachine::executeAction(AssignCompilerToken* compilerToken)
{
	//TODO: -=, +=, etc...
	
	updateVariable(compilerToken->getName(), executeReturnValue(compilerToken->getReturnValue()));

	currentAction = currentAction->getNextAction();
	//return action->getNextAction();
}

void VirtualMachine::executeAction(ConditionCompilerToken* compilerToken)
{
	//TODO: write this method
	//return nullptr;
}

void VirtualMachine::executeAction(FunctionCompilerToken* compilerToken)
{
	//TODO: write this method, if the function has a return type, do not forget to set the result! SJORS
	FunctionSymbol* fs = currentSymbolTable->getFunctionSymbol(compilerToken->getName(), compilerToken->getArguments().size());
	if (fs->isInternal()) {
		if (fs->getName() == "print") {
			print(executeReturnValue(compilerToken->getArguments()[0]));
		}
	} else {
		FunctionCompilerToken* fct = (FunctionCompilerToken*)fs->getStartAction()->getCompilerToken();
		std::vector<std::string> argNames = fct->getArgumentNames();
		for (int i = 0; i < argNames.size(); i++) {
			addVariable(argNames[i], executeReturnValue(compilerToken->getArguments()[i]));
		}
		Action* ca = fs->getStartAction();
		while (ca != fs->getEndAction()) {
			executeAction(ca->getCompilerToken());
		}

		currentAction = fs->getEndAction();
	}

	currentAction = currentAction->getNextAction();
}

void VirtualMachine::executeAction(SubConditionCompilerToken* compilerToken)
{
	//TODO: write this method
	//return nullptr;
}

void VirtualMachine::executeAction(VarCompilerToken* compilerToken)
{
	//TODO: use the correct symboltable with the corrosponding action
	boost::any value = currentSymbolTable->getValue(compilerToken->getName());

	TokenType frontOperator = compilerToken->getFrontOperator();
	TokenType backOperator = compilerToken->getBackOperator();

	if (frontOperator != TokenType::Null)
	{
		if (frontOperator == TokenType::IncreaseOperator)
		{
			if (value.type() == typeid(double))
			{
				double result = boost::any_cast<double>(value);
				result++;
				updateVariable(compilerToken->getName(), result);
				compilerToken->setResult(result);
			}
			else
			{
				throw new exception; //You can only do increase on a number. TODO: better exception handling
			}
		}
		else if (frontOperator == TokenType::DecreaseOperator)
		{
			if (value.type() == typeid(double))
			{
				double result = boost::any_cast<double>(value);
				result--;
				updateVariable(compilerToken->getName(), result);
				compilerToken->setResult(result);
			}
			else
			{
				throw new exception; //You can only do decrease on a number. TODO: better exception handling
			}
		}
	}
	else if (backOperator != TokenType::Null)
	{
		if (backOperator == TokenType::IncreaseOperator)
		{
			if (value.type() == typeid(double))
			{
				double result = boost::any_cast<double>(value);
				compilerToken->setResult(result);
				result++;
				updateVariable(compilerToken->getName(), result);
			}
			else
			{
				throw new exception; //You can only do increase on a number. TODO: better exception handling
			}
		}
		else if (backOperator == TokenType::DecreaseOperator)
		{
			if (value.type() == typeid(double))
			{
				double result = boost::any_cast<double>(value);
				compilerToken->setResult(result);
				result--;
				updateVariable(compilerToken->getName(), result);
			}
			else
			{
				throw new exception; //You can only do decrease on a number. TODO: better exception handling
			}
		}
	}
	else
	{
		compilerToken->setResult(value);
	}
	if (currentAction->getNextAction() != nullptr)
		currentAction = currentAction->getNextAction();
}

void VirtualMachine::addVariable(std::string name, boost::any value) {
	currentSymbolTable->addSymbolToTable(name, value);
}

boost::any VirtualMachine::executeReturnValue(ReturnValueCompilerToken* returnValueCompilerToken)
{
	//TODO: write this methods
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

			executeAction(varCompilerToken);

			resultStack.push(varCompilerToken->getResult());
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