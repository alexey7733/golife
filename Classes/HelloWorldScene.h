#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Hud.h"

class Playboard;

class HelloWorld : public cocos2d::Scene,
	public HudObserver
{
public:
	virtual ~HelloWorld();
    static cocos2d::Scene* create();

	// From HudObserver
	virtual void onStartPressed();
	virtual void onNextPressed();
	virtual void onStopPressed();
	virtual void onPlayboardSizeChanged(int x, int y);

	void update(float dt);

private:
	void updatePlayboard();
	void updateClock(float dt);

private:

	HelloWorld();
	virtual bool init();

private:
	Hud *hud;
	int sec;
	float clockTimer;
	float goverTimer;
	Playboard* playboard;
	cocos2d::Label* labelStatus;
};

#endif // __HELLOWORLD_SCENE_H__
