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
	Action *action = firstAction;

	while (action != nullptr)
	{
		try
		{
			//TODO: set the currentsymboltable from the information from the current action
			//TODO: donothingaction

			CompilerToken* compilerToken = action->getCompilerToken();

			if (compilerToken == nullptr) //this is DoNothingAction
			{
				action = action->getNextAction();
			}
			else if (typeid(*compilerToken) == typeid(AssignCompilerToken))
			{
				action = executeAction(action, (AssignCompilerToken*)action->getCompilerToken());
			}
		}
		catch (exception e)
		{
			//TODO: runtime error handling
			throw e;
		}
	}
}


void VirtualMachine::updateVariable(string name, boost::any value)
{
	currentSymbolTable->updateExistingSymbol(name, value);
}

Action* VirtualMachine::executeAction(Action* action, AssignCompilerToken* compilerToken)
{
	//TODO: -=, +=, etc...
	std::stack<double> resultStack;
	ReturnValueCompilerToken* returnValueCompilerToken = compilerToken->getReturnValue();
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
			double b = resultStack.top();
			resultStack.pop();
			double a = resultStack.top();
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

			executeAction(action, varCompilerToken);

			resultStack.push(boost::any_cast<double>(varCompilerToken->getResult()));
		}
		else //it is a function
		{
			FunctionCompilerToken* functionCompilerToken = boost::any_cast<FunctionCompilerToken*>(value);

			executeAction(action, functionCompilerToken);

			resultStack.push(boost::any_cast<double>(functionCompilerToken->getResult()));
		}
	}

	double result = resultStack.top();

	updateVariable(compilerToken->getName(), result);

	return action->getNextAction();
}

Action* VirtualMachine::executeAction(Action* action, ConditionCompilerToken* compilerToken)
{
	//TODO: write this method
	return nullptr;
}

Action* VirtualMachine::executeAction(Action* action, FunctionCompilerToken* compilerToken)
{
	//TODO: write this method, if the function has a return type, do not forget to set the result! SJORS

	return action->getNextAction();
}

Action* VirtualMachine::executeAction(Action* action, SubConditionCompilerToken* compilerToken)
{
	//TODO: write this method
	return nullptr;
}

Action* VirtualMachine::executeAction(Action* action, ReturnValueCompilerToken* compilerToken)
{
	//TODO: write this methods
	return nullptr;
}

Action* VirtualMachine::executeAction(Action* action, VarCompilerToken* compilerToken)
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

	return action->getNextAction();
}