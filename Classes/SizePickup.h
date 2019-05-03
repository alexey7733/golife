#ifndef __SIZEPICKUP_H__
#define __SIZEPICKUP_H__

#include "cocos2d.h"

class SizePickup;

class SizePickupObserver
{
public:
	virtual void onSizePickupValueChanged() = 0;
};

class SizePickup : public cocos2d::LayerColor
{
public:
	virtual ~SizePickup();
    static SizePickup* create(int range, int value);

	void setObserver(SizePickupObserver* o);

	void setMenuActive(bool flag);

	int getValue();

	static cocos2d::Size getSize();

private:
	SizePickup(int range, int value);
	virtual bool init();

private:
	void updateLabel();
	void onLeftPressed();
	void onRightPressed();

private:
	int value;
	int range;
	cocos2d::Menu* menu;
	cocos2d::Label* label;
	SizePickupObserver* observer;
};

#endif // __SIZEPICKUP_H__
