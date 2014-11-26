#pragma once
#include "IInternalFunction.h"
#include <memory>
#include <string>
#include <map>
#include <functional>

// Example 
//std::shared_ptr<IinternalFunction> instance = InternalFunctionFactory::Instance()->Create("pow");
//instance->Execute(std::vector<boost::any>{2.0, 3.0});

class Register {
public:
	Register(std::string className, std::function<IInternalFunction*(void)> classFactoryFunction);
};

#define REGISTER_CLASS(NAME, TYPE) static Register _register(NAME, [](void) -> IInternalFunction * { return new TYPE();});

// The factory - implements singleton pattern!
class InternalFunctionFactory
{
public:
	// Get the single instance of the factory
	static InternalFunctionFactory * Instance();

	// register a factory function to create an instance of className
	void RegisterFactoryFunction(std::string name, std::function<IInternalFunction*(void)> classFactoryFunction);

	// create an instance of a registered class
	std::shared_ptr<IInternalFunction> Create(std::string name);
	const std::map<std::string, std::function<IInternalFunction*(void)>> GetMap();

private:
	// a private ctor
	InternalFunctionFactory(){}

	// the registry of factory functions
	std::map<std::string, std::function<IInternalFunction*(void)>> factoryFunctionRegistry;
	static InternalFunctionFactory *factory;

};