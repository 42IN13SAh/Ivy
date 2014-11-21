#include "Factory.h"

Registrar::Registrar(std::string name, std::function<IinternalFunction*(void)> classFactoryFunction)
{
	// register the class factory function
	MyFactory::Instance()->RegisterFactoryFunction(name, classFactoryFunction);
}

MyFactory * MyFactory::Instance()
{
	static MyFactory factory;
	return &factory;
}


void MyFactory::RegisterFactoryFunction(std::string name, std::function<IinternalFunction*(void)> classFactoryFunction)
{
	// register the class factory function 
	factoryFunctionRegistry[name] = classFactoryFunction;
}


std::shared_ptr<IinternalFunction> MyFactory::Create(std::string name)
{
	IinternalFunction * instance = nullptr;

	// find name in the registry and call factory method.
	auto it = factoryFunctionRegistry.find(name);
	if (it != factoryFunctionRegistry.end())
		instance = it->second();

	// wrap instance in a shared ptr and return
	if (instance != nullptr)
		return std::shared_ptr<IinternalFunction>(instance);
	else
		return nullptr;
}