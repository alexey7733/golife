#ifndef __PLAYBOARD_ITEM_H__
#define __PLAYBOARD_ITEM_H__

#include "cocos2d.h"
#include "Utils.h"

class PlayboardItem;

class PlayboardItemObserver
{
public:
	virtual void onPlayboardItemCliked(PlayboardItem* i) = 0;
};

class PlayboardItem : public cocos2d::MenuItemImage
	//public cocos2d::LayerColor
{
public:
	enum State
	{
		Live = 1,
		Dead
	};
public:
	virtual ~PlayboardItem();
    static PlayboardItem* create();

	void setObserver(PlayboardItemObserver* o);

	static cocos2d::Size getSize();

	GridIndex getIndex();
	void setIndex(int row, int col);

	State getState();
	void setState(State s);

private:
	void onItemClicked();
	void updateColor();

private:
	PlayboardItem();
	virtual bool init();
private:
	State state;
	GridIndex index;
	//cocos2d::Label* label;
	PlayboardItemObserver* observer;
};

#endif // __PLAYBOARD_ITEM_H__
