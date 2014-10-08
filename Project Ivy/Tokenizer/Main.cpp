#include "Tokenizer.h"

int main()
{
	Tokenizer *tokenizer = new Tokenizer();

	std::string code[] { 
			"main(string tekst, int getal) { return 13; }", 
			"cout << 42;" };

	tokenizer->tokenize(code, 2);

	return 0;
}