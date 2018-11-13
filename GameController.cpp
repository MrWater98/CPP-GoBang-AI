#include "GameController.h"

GameController::GameController()
{
    //ctor
}

GameController::~GameController()
{
    //dtor
}
GameController* GameController::instance = nullptr;
GameController* GameController::getInstance()
{

    if(!instance)
    {
        instance = new GameController();
    }
    return instance;
}
