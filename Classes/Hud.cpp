#include "Hud.h"
#include "Playboard.h"
#include "SizePickup.h"
#include "Colors.h"

USING_NS_CC;

////////////////////////////////////////////////////////////////////////////////

static const float WIDTH = 248;
static const float HEIGHT = 760;

static const float BUTTON_WIDTH = 170;
static const float BUTTON_HEIGHT = 64;

////////////////////////////////////////////////////////////////////////////////

Hud::Hud()
: pickWidth(0)
, pickHeight(0)
, observer(0)
, labelClock(0)
{
	//
}

Hud::~Hud()
{
	//
}

Hud* Hud::create()
{
	Hud* pb = new Hud();

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

bool Hud::init()
{
	if (!initWithColor(Color4B(0, 0, 255, 255)))
		return false;

	Size size(WIDTH, HEIGHT);

	setContentSize(size);

	Vec2 grid = Playboard::getGridMaxSize();

	const float MARGIN = 20;

	pickWidth = SizePickup::create(grid.x, grid.x);
	pickWidth->setObserver(this);
	Size wSize = pickWidth->getContentSize();
	pickWidth->setPosition(size.width / 2 - wSize.width / 2, size.height - wSize.height - MARGIN);
	addChild(pickWidth);

	pickHeight = SizePickup::create(grid.y, grid.y);
	pickHeight->setObserver(this);
	Size hSize = pickHeight->getContentSize();
	pickHeight->setPosition(pickWidth->getPositionX(), pickWidth->getPositionY() - wSize.height - MARGIN);
	addChild(pickHeight);

	const char *font = "fonts/arial.ttf";

	const float FONT_SIZE = 36;

	LayerColor* nodeClock = LayerColor::create(BUTTON_COLOR, BUTTON_WIDTH, BUTTON_HEIGHT);
	nodeClock->setPosition(size.width / 2 - nodeClock->getContentSize().width / 2, 
		pickHeight->getPositionY() - nodeClock->getContentSize().height - MARGIN);
	labelClock = Label::createWithTTF("00:00", font, FONT_SIZE, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	labelClock->setPosition(nodeClock->getContentSize().width / 2, nodeClock->getContentSize().height / 2);
	nodeClock->addChild(labelClock);
	addChild(nodeClock);

	Vector<MenuItem*> menuItems;

	LayerColor* nodePlay = LayerColor::create(BUTTON_COLOR, BUTTON_WIDTH, BUTTON_HEIGHT);
	Label* labelPlay = Label::createWithTTF("START", font, FONT_SIZE, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	labelPlay->setPosition(nodePlay->getContentSize().width / 2, nodePlay->getContentSize().height / 2);
	nodePlay->addChild(labelPlay);
	MenuItemLabel* btnPlay = MenuItemLabel::create(nodePlay, CC_CALLBACK_0(Hud::onStartPressed, this));
	btnPlay->setPosition(size.width / 2, nodeClock->getPositionY() - nodePlay->getContentSize().height / 2 - MARGIN);
	menuItems.pushBack(btnPlay);

	LayerColor* nodeNext = LayerColor::create(BUTTON_COLOR, BUTTON_WIDTH, BUTTON_HEIGHT);
	Label* labelNext = Label::createWithTTF("NEXT", font, FONT_SIZE, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	labelNext->setPosition(nodeNext->getContentSize().width / 2, nodeNext->getContentSize().height / 2);
	nodeNext->addChild(labelNext);
	MenuItemLabel* btnNext = MenuItemLabel::create(nodeNext, CC_CALLBACK_0(Hud::onNextPressed, this));
	btnNext->setPosition(size.width / 2, btnPlay->getPositionY() - nodePlay->getContentSize().height / 2 - nodeNext->getContentSize().height / 2 - MARGIN);
	menuItems.pushBack(btnNext);

	LayerColor* nodeStop = LayerColor::create(BUTTON_COLOR, BUTTON_WIDTH, BUTTON_HEIGHT);
	Label* labelStop = Label::createWithTTF("STOP", font, FONT_SIZE, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	labelStop->setPosition(nodeStop->getContentSize().width / 2, nodeStop->getContentSize().height / 2);
	nodeStop->addChild(labelStop);
	MenuItemLabel* btnStop = MenuItemLabel::create(nodeStop, CC_CALLBACK_0(Hud::onStopPressed, this));
	btnStop->setPosition(size.width / 2, btnNext->getPositionY() - btnNext->getContentSize().height / 2 - nodeStop->getContentSize().height / 2 - MARGIN);
	menuItems.pushBack(btnStop);

	Menu* menu = Menu::createWithArray(menuItems);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	return true;
}

void Hud::setObserver(HudObserver* o)
{
	observer = o;
}

Size Hud::getSize()
{
	return Size(WIDTH, HEIGHT);
}

void Hud::onSizePickupValueChanged()
{
	int x = pickWidth->getValue();
	int y = pickHeight->getValue();

	if (observer)
		observer->onPlayboardSizeChanged(x, y);
}

void Hud::onStartPressed()
{
	if (observer)
		observer->onStartPressed();
}

void Hud::onNextPressed()
{
	if (observer)
		observer->onNextPressed();
}

void Hud::onStopPressed()
{

	if (observer)
		observer->onStopPressed();
}

void Hud::updateClock(int m, int s)
{
	CCLOG("Hud::updateClock() %02d:%02d", m, s);

	char buf[64] = { 0 };

	unsigned int size = sizeof(buf);

	snprintf(buf, size, "%02d:%02d", m, s);

	//std::string res = buf;
	labelClock->setString(buf);
}
