#include "PlayboardItem.h"
#include "Utils.h"
#include "Colors.h"
#include "GameController.h"
#include <string>

USING_NS_CC;

////////////////////////////////////////////////////////////////////////////////

// IMPORTANT! has to be the same as 64x64.png sprite
static const float WIDTH = 64;
static const float HEIGHT = 64;

////////////////////////////////////////////////////////////////////////////////

PlayboardItem::PlayboardItem()
	: state(Dead)
	//, label(0)
	, observer(0)
{
	//
}

PlayboardItem::~PlayboardItem()
{
	//
}

PlayboardItem* PlayboardItem::create()
{
	PlayboardItem* pb = new PlayboardItem();

	if (pb && pb->init())
	{
		pb->autorelease();
	}
	else
	{
		delete pb;
		pb = 0;
	}

	return pb;
}

bool PlayboardItem::init()
{
	//if (!initWithColor(Color4B(0, 255, 0, 255)))
	//	return false;

	if (!initWithNormalImage("64x64.png", "", "", CC_CALLBACK_0(PlayboardItem::onItemClicked, this)))
		return false;

	Size size(WIDTH, HEIGHT);

	setContentSize(size);

	const char *font = "fonts/arial.ttf";

	/*label = Label::createWithTTF("", font, 18, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	label->setColor(Color3B(0, 0, 0));
	label->setPosition(size.width / 2, size.height / 2);
	addChild(label);*/

	updateColor();

	return true;
}

void PlayboardItem::setObserver(PlayboardItemObserver* o)
{
	observer = o;
}

Size PlayboardItem::getSize()
{
	return Size(WIDTH, HEIGHT);
}

GridIndex PlayboardItem::getIndex()
{
	return index;
}

void PlayboardItem::setIndex(int row, int col)
{
	index.setRow(row);
	index.setCol(col);

	//std::string rs = Utils::intToString(row);
	//std::string cs = Utils::intToString(col);
	//std::string res = rs + ", " + cs;
	//label->setString(res);
}

void PlayboardItem::onItemClicked()
{
	if (GameController::instance()->getState() != GameController::None)
		return;

	//CCLOG("PlayboardItem::onItemClicked() [%d, %d]", index.getRow(), index.getCol());

	setState(state == Dead ? Live : Dead);

	if (observer)
		observer->onPlayboardItemCliked(this);
}

PlayboardItem::State PlayboardItem::getState()
{
	return state;
}

void PlayboardItem::setState(State s)
{
	state = s;

	updateColor();
}

void PlayboardItem::updateColor()
{
	if (state == Live)
		getNormalImage()->setColor(LIVE_COLOR);
	else
		getNormalImage()->setColor(DEAD_COLOR);
}
