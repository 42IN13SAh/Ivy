#pragma once
#include "IinternalFunction.h"
#include <memory>
#include <string>
#include <map>
#include <functional>

// Example 
//std::shared_ptr<IinternalFunction> instance = MyFactory::Instance()->Create("pow");
//instance->Execute(std::vector<boost::any>{2.0, 3.0});

class Registrar {
public:
	Registrar(std::string className, std::function<IinternalFunction*(void)> classFactoryFunction);
};

#define REGISTER_CLASS(NAME, TYPE) static Registrar registrar(NAME, [](void) -> IinternalFunction * { return new TYPE();});

// The factory - implements singleton pattern!
class MyFactory
{
public:
	// Get the single instance of the factory
	static MyFactory * Instance();

	// register a factory function to create an instance of className
	void RegisterFactoryFunction(std::string name, std::function<IinternalFunction*(void)> classFactoryFunction);

	// create an instance of a registered class
	std::shared_ptr<IinternalFunction> Create(std::string name);

private:
	// a private ctor
	MyFactory(){}

	// the registry of factory functions
	std::map<std::string, std::function<IinternalFunction*(void)>> factoryFunctionRegistry;

};