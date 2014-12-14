#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H
#include <string>

class MainWindow;
class Tokenizer;
class Compiler;
class VirtualMachine;

class BaseController
{
public:
    BaseController(MainWindow *source);
	virtual ~BaseController();
protected:
	bool startBuilding(bool onlyBuild);
    void startRunning();
	void saveCurrentFile();
	void saveNewFile(std::string filePath);

	bool fileExists(const std::string& filename);

	std::string ExePath();
	MainWindow *source; //TODO: find better name?

private:
	Tokenizer *tokenizer;
	Compiler *compiler;
	VirtualMachine *virtualMachine;

	std::string currentFilePath;
};

#endif // BASECONTROLLER_H
