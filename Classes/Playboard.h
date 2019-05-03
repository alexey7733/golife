#ifndef __PLAYBOARD_SCENE_H__
#define __PLAYBOARD_SCENE_H__

#include "cocos2d.h"

const int GRID_MAX = 10;

class PlayboardItem;

class Playboard : public cocos2d::Node
	//public cocos2d::LayerColor
{
public:
	virtual ~Playboard();
    static Playboard* create();

	static cocos2d::Vec2 getGridMaxSize();

	cocos2d::Vec2 getGridSize();
	void setGridSize(int x, int y);

	bool updatePlayboard();

	void resetPlayboard();

private:
	void createItems();

private:
	Playboard();
	virtual bool init();

private:
	int gridx;
	int gridy;
	cocos2d::Menu* menu;
	PlayboardItem* itemArray[GRID_MAX][GRID_MAX];
};

#endif // __PLAYBOARD_SCENE_H__
