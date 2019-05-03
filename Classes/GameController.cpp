#include "GameController.h"

GameController* GameController::obj = 0;

GameController::GameController()
	: state(None)
{
	//
}

GameController::~GameController()
{
	//
}

GameController* GameController::instance()
{
	if (obj == 0)
	{
		obj = new GameController();
		obj->init();
	}

	return obj;
}

void GameController::release()
{
	if (obj)
	{
		delete obj;
		obj = 0;
	}
}

void GameController::init()
{
	//
}

GameController::State GameController::getState()
{
	return state;
}

void GameController::setState(State s)
{
	state = s;
}
