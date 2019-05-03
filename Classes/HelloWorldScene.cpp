#include "HelloWorldScene.h"
#include "Hud.h"
#include "Playboard.h"
#include "Utils.h"
#include "GameController.h"

USING_NS_CC;

static const float STATE_DURATION = 5;
static const float GOVER_DURATION = 2;

Scene* HelloWorld::create()
{
	HelloWorld* hw = new HelloWorld();

	if (hw && hw->init())
	{
		hw->autorelease();
	}
	else
	{
		delete hw;
		hw = 0;
	}

	return hw;
}

HelloWorld::HelloWorld()
	: hud(0)
	, sec(0)
	, clockTimer(0)
	, goverTimer(0)
	, playboard(0)
	, labelStatus(0)
{
	//
}

HelloWorld::~HelloWorld()
{
	GameController::instance()->release();
}

bool HelloWorld::init()
{
    if (!Scene::init())
		return false;

	GameController::instance(); // initialize

    auto visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

	playboard = Playboard::create();
	addChild(playboard);

	hud = Hud::create();
	hud->setObserver(this);
	Size hSize = Hud::getSize();
	float hMargin = (visibleSize.height - hSize.height) / 2;
	hud->setPosition(visibleSize.width - hMargin - hSize.width, hMargin);
	addChild(hud);

	const char *font = "fonts/arial.ttf";

	// playboard area
	float areaw = visibleSize.width - hSize.width;

	labelStatus = Label::createWithTTF("GAME OVER", font, 48, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	labelStatus->setVisible(false);
	labelStatus->setPosition(areaw / 2, visibleSize.height / 2);
	addChild(labelStatus);

	// init playboard
	Vec2 grid = Playboard::getGridMaxSize();
	onPlayboardSizeChanged(grid.x, grid.y);

	scheduleUpdate();

    return true;
}

void HelloWorld::update(float dt)
{
	if (GameController::instance()->getState() == GameController::State::None)
		return;

	// animate game over label
	if (GameController::instance()->getState() == GameController::State::Over)
	{
		goverTimer += dt;

		// game over animation completed
		if (goverTimer > GOVER_DURATION || Utils::isEqual(GOVER_DURATION, goverTimer))
		{
			goverTimer = 0;

			labelStatus->setVisible(false);

			GameController::instance()->setState(GameController::State::None);

			playboard->resetPlayboard();
		}

		return;
	}

	updateClock(dt);

	if (sec == 0 && Utils::isEqual(clockTimer, 0))
	{
		updatePlayboard();
	}
}

void HelloWorld::updateClock(float dt)
{
	clockTimer += dt;

	if (clockTimer > 1 || Utils::isEqual(clockTimer, 1))
	{
		--sec;

		if (sec < 0)
			sec = STATE_DURATION;

		clockTimer = 0;

		hud->updateClock(0, sec);
	}
}

void HelloWorld::updatePlayboard()
{
	CCLOG("HelloWorld::updatePlayboard() sec=%d", sec);

	bool gameover = playboard->updatePlayboard();

	if (gameover)
	{
		goverTimer = 0;

		labelStatus->setVisible(true);

		GameController::instance()->setState(GameController::Over);
	}
}

void HelloWorld::onStartPressed()
{
	if (GameController::instance()->getState() != GameController::None)
		return;

	GameController::instance()->setState(GameController::Play);

	goverTimer = 0;

	clockTimer = 0;

	sec = STATE_DURATION;

	hud->updateClock(0, sec);
}

void HelloWorld::onNextPressed()
{
	// TODO: check if in play state ?

	updatePlayboard();

	clockTimer = 0;

	sec = STATE_DURATION;

	hud->updateClock(0, sec);
}

void HelloWorld::onStopPressed()
{
	if (GameController::instance()->getState() == GameController::State::None)
		return;

	GameController::instance()->setState(GameController::None);

	goverTimer = 0;

	labelStatus->setVisible(true);

	GameController::instance()->setState(GameController::Over);
}

void HelloWorld::onPlayboardSizeChanged(int x, int y)
{
	//CCLOG("HelloWorld::onPlayboardSizeChanged() x=%d y=%d", x, y);

	if (GameController::instance()->getState() != GameController::None)
		return;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size hSize = Hud::getSize();

	float areaw = visibleSize.width - hSize.width;
	float areah = visibleSize.height;

	playboard->setGridSize(x, y);
	Size pSize = playboard->getContentSize();
	playboard->setPosition((areaw - pSize.width) / 2, (areah - pSize.height) / 2);
}
