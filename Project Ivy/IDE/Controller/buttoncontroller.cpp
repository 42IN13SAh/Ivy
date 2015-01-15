#include "buttoncontroller.h"
#include <qdebug.h>
#include <future>

ButtonController::ButtonController(MainWindow * source) : BaseController(source)
{
}

ButtonController::~ButtonController()
{

}

void ButtonController::runButtonClicked()
{
	std::async(std::launch::async, [&]() {
		startRunning();
	});
}

void ButtonController::buildButtonClicked()
{
	std::async(std::launch::async, [&]() {
		startBuilding(true, true);
	});
}
