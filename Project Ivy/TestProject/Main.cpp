#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include "Tokenizer.h"
#include "Compiler.h"
#include "VirtualMachine.h"

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Tokenizer* tok = new Tokenizer();
	std::string line;
	std::vector<std::string> lines;
	std::ifstream file;
	file.open("code.txt");
	while (std::getline(file, line)){
		lines.push_back(line);
		std::cout << line << std::endl;
	}
	file.close();
	tok->tokenize(&lines[0], lines.size());
	Compiler* comp = new Compiler(tok->getTokenList());
	comp->compile();

	VirtualMachine* vm = new VirtualMachine(comp->getSymbolTable());
	vm->run(comp->getFirstAction());

	delete tok;
	delete vm;
	delete comp;
}