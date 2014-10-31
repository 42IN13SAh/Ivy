#include <fstream>

#include "..\Tokenizer\Tokenizer.h"
#include "..\Compiler\Compiler.h"
#include "..\Virtual Machine\VirtualMachine.h"
#include "Jzon.h"

int main(){
	Tokenizer tok;
	std::string line;
	std::vector<string> lines;
	std::ifstream file;
	file.open("test code 1.0.txt");
	while (std::getline(file, line)){
		lines.push_back(line);
	}
	file.close();
	tok.tokenize(&lines[0], lines.size());

	Compiler *comp = new Compiler(tok.getTokenList());
	//Execute compiler related tasks below

	
	
	VirtualMachine vm;
	//Execute VM related tasks below



	return 0;
}