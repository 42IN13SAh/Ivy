#include "basecontroller.h"
#include <qdebug.h>
#include "mainwindow.h"

BaseController::BaseController(MainWindow * source)
{
	this->source = source;
}

void BaseController::startTokenizing(){
	std::vector<std::string> list = source->getEditorContent();

    qDebug() << "Came into the 'startTokenizing' function in basecontroller";
}

void BaseController::startCompiling(){
    //TODO: implement
    qDebug() << "Came into the 'startCompiling' function in basecontroller";
}

void BaseController::startRunning(){
    //TODO implement
    qDebug() << "Came into the 'startRunning' function in basecontroller";
}
