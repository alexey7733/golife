#include "SizePickup.h"
#include "GameController.h"
#include "Utils.h"
#include "Colors.h"

USING_NS_CC;

////////////////////////////////////////////////////////////////////////////////

static const float WIDTH = 128;
static const float HEIGHT = 64;

////////////////////////////////////////////////////////////////////////////////

SizePickup::SizePickup(int r, int v)
	: menu(0)
	, value(v)
	, range(r)
	, label(0)
	, observer(0)
{
	//
}

SizePickup::~SizePickup()
{
	//
}

SizePickup* SizePickup::create(int range, int value)
{
	SizePickup* pb = new SizePickup(range, value);

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

bool SizePickup::init()
{
	if (!initWithColor(BUTTON_COLOR))
		return false;

	const char *font = "fonts/arial.ttf";

	Vector<MenuItem*> menuItems;

	const float FONT_SIZE = 36;

	Label* arrow1 = Label::createWithTTF("<", font, FONT_SIZE, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Size a1Size = arrow1->getContentSize();
	MenuItemLabel* btnLeft = MenuItemLabel::create(arrow1, CC_CALLBACK_0(SizePickup::onLeftPressed, this));
	btnLeft->setPosition(a1Size.width / 2, HEIGHT / 2);
	menuItems.pushBack(btnLeft);

	std::string str = Utils::intToString(range);

	label = Label::createWithTTF(str, font, FONT_SIZE, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Size lSize = label->getContentSize();
	label->setPosition(btnLeft->getPositionX() + a1Size.width / 2 + WIDTH / 2, btnLeft->getPositionY());
	addChild(label);

	Label* arrow2 = Label::createWithTTF(">", font, FONT_SIZE, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Size a2Size = arrow2->getContentSize();
	MenuItemLabel* btnRight = MenuItemLabel::create(arrow2, CC_CALLBACK_0(SizePickup::onRightPressed, this));
	btnRight->setPosition(label->getPositionX() + WIDTH / 2 + a2Size.width / 2, btnLeft->getPositionY());
	menuItems.pushBack(btnRight);

	menu = Menu::createWithArray(menuItems);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	float w = a1Size.width + WIDTH + a2Size.width;
	float h = HEIGHT;

	Size size(w, h);

	setContentSize(size);

	updateLabel();

	return true;
}

void SizePickup::setObserver(SizePickupObserver* o)
{
	observer = o;
}

void SizePickup::setMenuActive(bool flag)
{
	// TODO: update color ?
	menu->setEnabled(flag);
}

Size SizePickup::getSize()
{
	return Size(WIDTH, HEIGHT);
}

void SizePickup::updateLabel()
{
	std::string str = Utils::intToString(value);

	label->setString(str);
}

void SizePickup::onLeftPressed()
{
	if (GameController::instance()->getState() != GameController::State::None)
		return;

	--value;

	if (value < 1)
		value = 1;

	updateLabel();

	if (observer)
		observer->onSizePickupValueChanged();
}

void SizePickup::onRightPressed()
{
	if (GameController::instance()->getState() != GameController::State::None)
		return;

	++value;

	if (value > range)
		value = range;

	updateLabel();

	if (observer)
		observer->onSizePickupValueChanged();
}

int SizePickup::getValue()
{
	return value;
}
