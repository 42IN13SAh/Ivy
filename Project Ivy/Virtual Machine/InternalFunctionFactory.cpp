#include "InternalFunctionFactory.h"

//InternalFunctionFactory* InternalFunctionFactory::factory = nullptr;

InternalFunctionFactory::InternalFunctionFactory()
{
	//Date
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("date", new Date(), 0);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("dateTime", new DateTime(), 0);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("time", new Time(), 0);
	//I/O
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("readFile", new ReadFile(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("readFileLines", new ReadFileLines(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("saveFile", new SaveFile(), 2);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("writeToEndOfFile", new WriteToEndOfFile(), 2);
	//Math
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("cos", new Cos(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("invert", new Invert(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("log", new Log(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("pow", new Pow(), 2);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("random", new Random(), 2);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("sin", new Sin(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("squareRoot", new SquareRoot(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("tan", new Tan(), 1);
	//System
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("consoleInput", new ConsoleInput(), 0);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("formatString", new FormatString(), 100);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("print", new Print(), 1);
}

InternalFunctionFactory* InternalFunctionFactory::Instance()
{
	static InternalFunctionFactory instance;
	/*if (factory == nullptr)
		factory = new InternalFunctionFactory();*/

	return &instance;
}


void InternalFunctionFactory::RegisterFactoryFunction(std::string name, IInternalFunction* classFactoryFunction, int argNr)
{
	// register the class factory function 
	factoryFunctionRegistry[name] = classFactoryFunction;
	factoryFunctionArgNrRegistry[name] = argNr;
}


std::shared_ptr<IInternalFunction> InternalFunctionFactory::Create(std::string name)
{
	IInternalFunction * instance = nullptr;

	// find name in the registry and call factory method.
	auto it = factoryFunctionRegistry.find(name);
	if (it != factoryFunctionRegistry.end())
		instance = it->second;

	// wrap instance in a shared ptr and return
	if (instance != nullptr)
		return std::shared_ptr<IInternalFunction>(instance);
	else
		return nullptr;
}

const std::map<std::string, IInternalFunction*> InternalFunctionFactory::GetMap()
{
	return factoryFunctionRegistry;
}

const std::map<std::string, int> InternalFunctionFactory::GetArgNrMap()
{
	return factoryFunctionArgNrRegistry;
}