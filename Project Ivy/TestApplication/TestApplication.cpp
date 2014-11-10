#include <fstream>
#include <iostream>
#include <chrono>

#include "..\Tokenizer\Tokenizer.h"
#include "..\Compiler\Compiler.h"
#include "..\Virtual Machine\VirtualMachine.h"
#include "Jzon.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(){
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Tokenizer* tok = new Tokenizer();
	std::string line;
	std::vector<string> lines;
	std::ifstream file;
	file.open("test code small.txt");
	while (std::getline(file, line)){
		lines.push_back(line);
		std::cout << line << endl;
	}
	file.close();
	//lines.push_back('\0');
	
	//Execute compiler related tasks below
	//auto start_time = std::chrono::high_resolution_clock::now();
	tok->tokenize(&lines[0], lines.size());

	Compiler* comp = new Compiler(tok->getTokenList());
	comp->compile();

	VirtualMachine* vm = new VirtualMachine(comp->getSymbolTable());
	vm->run(comp->getFirstAction());

	std::string msg;
	std::cin >> msg;
	
	delete comp;
	delete tok;
	delete vm;
	/*auto end_time = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
	std::getchar();*/

	//comp->getFirstAction()->getNextAction()->getCompilerToken()->toString();
	
	//Execute VM related tasks below


	return 0;
}