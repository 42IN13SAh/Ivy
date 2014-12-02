#pragma once
#include "IInternalFunction.h"
#include <memory>
#include <string>
#include <map>
#include <functional>

#include "Date.h"
#include "DateTime.h"
#include "Time.h"

#include "ReadFile.h"
#include "ReadFileLines.h"
#include "SaveFile.h"
#include "WriteToEndOfFile.h"

#include "Cos.h"
#include "Log.h"
#include "Pow.h"
#include "Sin.h"
#include "SquareRoot.h"
#include "Tan.h"
#include "Invert.h"
#include "Random.h"

#include "ConsoleInput.h"
#include "FormatString.h"
#include "Print.h"

// Example 
//std::shared_ptr<IinternalFunction> instance = InternalFunctionFactory::Instance()->Create("pow");
//instance->Execute(std::vector<boost::any>{2.0, 3.0});

//class Register {
//public:
//	//Register(std::string className, std::function<IInternalFunction*(void)> classFactoryFunction);
//	Register(std::string className, std::function<IInternalFunction*(void)> classFactoryFunction, int argNr);
//};

//#define REGISTER_CLASS(NAME, TYPE) static Register _register(NAME, [](void) -> IInternalFunction * { return new TYPE();});
//#define REGISTER_CLASS(NAME, TYPE, ARGNR) static Register _register(NAME, [](void) -> IInternalFunction * { return new TYPE();}, ARGNR);

// The factory - implements singleton pattern!
class InternalFunctionFactory
{
public:
	InternalFunctionFactory();
	~InternalFunctionFactory();
	// Get the single instance of the factory
	static InternalFunctionFactory * Instance();

	// register a factory function to create an instance of className
	//void RegisterFactoryFunction(std::string name, std::function<IInternalFunction*(void)> classFactoryFunction);
	void RegisterFactoryFunction(std::string name, IInternalFunction* classFactoryFunction, int argNr);

	// create an instance of a registered class
	IInternalFunction* Create(std::string name);
	const std::map<std::string, IInternalFunction*> GetMap();
	const std::map<std::string, int> GetArgNrMap();

private:
	// the registry of factory functions
	std::map<std::string, IInternalFunction*> factoryFunctionRegistry;
	std::map<std::string, int> factoryFunctionArgNrRegistry;

	//static InternalFunctionFactory* factory;
};
