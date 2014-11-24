#include "InternalFunctionFactory.h"

Registrar::Registrar(std::string name, std::function<IInternalFunction*(void)> classFactoryFunction)
{
	// register the class factory function
	InternalFunctionFactory::Instance()->RegisterFactoryFunction(name, classFactoryFunction);
}

InternalFunctionFactory * InternalFunctionFactory::Instance()
{
	if (factory == nullptr)
		factory = new InternalFunctionFactory();
	return factory;
}


void InternalFunctionFactory::RegisterFactoryFunction(std::string name, std::function<IInternalFunction*(void)> classFactoryFunction)
{
	// register the class factory function 
	factoryFunctionRegistry[name] = classFactoryFunction;
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