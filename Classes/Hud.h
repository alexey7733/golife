#ifndef __HOOD_H__
#define __HOOD_H__

#include "cocos2d.h"
#include "SizePickup.h"

class SizePickup;

class HudObserver
{
public:
	virtual void onStartPressed() = 0;
	virtual void onNextPressed() = 0;
	virtual void onStopPressed() = 0;
	virtual void onPlayboardSizeChanged(int x, int y) = 0;
};

class Hud : public cocos2d::LayerColor,
	public SizePickupObserver
{
public:
	virtual ~Hud();
    static Hud* create();

	void setObserver(HudObserver* o);
	static cocos2d::Size getSize();

	void updateClock(int m, int s);

	// From SizePickupObserver
	virtual void onSizePickupValueChanged();

private:
	void onStartPressed();
	void onNextPressed();
	void onStopPressed();

private:
	Hud();
	virtual bool init();

private:
	SizePickup* pickWidth;
	SizePickup* pickHeight;
	HudObserver* observer;
	cocos2d::Label* labelClock;
};

#endif // __HOOD_H__
