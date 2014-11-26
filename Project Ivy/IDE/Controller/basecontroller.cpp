#include "basecontroller.h"
#include <qdebug.h>

BaseController::BaseController()
{
    //TODO: load data from dll/lib here if needed (i.e. create tokenizer object that can be called if we really need that)
}

void BaseController::startTokenizing(){
    //TODO: implement
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
