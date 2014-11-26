#include "InternalFunctionFactory.h"

InternalFunctionFactory* InternalFunctionFactory::factory = nullptr;

Register::Register(std::string name, std::function<IInternalFunction*(void)> classFactoryFunction, int argNr)
{
	// register the class factory function
	InternalFunctionFactory::Instance()->RegisterFactoryFunction(name, classFactoryFunction, argNr);
}

InternalFunctionFactory* InternalFunctionFactory::Instance()
{
	if (!factory)
		factory = new InternalFunctionFactory;
	return factory;
}


void InternalFunctionFactory::RegisterFactoryFunction(std::string name, std::function<IInternalFunction*(void)> classFactoryFunction, int argNr)
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
		instance = it->second();

	// wrap instance in a shared ptr and return
	if (instance != nullptr)
		return std::shared_ptr<IInternalFunction>(instance);
	else
		return nullptr;
}

const std::map<std::string, std::function<IInternalFunction*(void)>> InternalFunctionFactory::GetMap()
{
	return factoryFunctionRegistry;
}

const std::map<std::string, int> InternalFunctionFactory::GetArgNrMap()
{
	return factoryFunctionArgNrRegistry;
}