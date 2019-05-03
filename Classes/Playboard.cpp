#include "Playboard.h"
#include "PlayboardItem.h"
#include <vector>

USING_NS_CC;

////////////////////////////////////////////////////////////////////////////////

static const float DIST_X = 4;
static const float DIST_Y = 4;

////////////////////////////////////////////////////////////////////////////////

Playboard::Playboard()
	: gridx(0)
	, gridy(0)
	, menu(0)
{
	//
}

Playboard::~Playboard()
{
	//
}

Playboard* Playboard::create()
{
	Playboard* pb = new Playboard();

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

bool Playboard::init()
{
	//if (!initWithColor(Color4B(255, 0, 0, 255)))
	//	return false;

	menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	createItems();

	Vec2 grid = Playboard::getGridMaxSize();

	setGridSize(grid.x, grid.y);

	return true;
}

cocos2d::Vec2 Playboard::getGridSize()
{
	return Vec2(gridx, gridy);
}

void Playboard::resetPlayboard()
{
	for (int col = 0; col < gridy; ++col)
	{
		for (int row = 0; row < gridx; ++row)
		{
			PlayboardItem* item = itemArray[row][col];

			item->setVisible(true);
			item->setState(PlayboardItem::Dead);
		}
	}
}

void Playboard::setGridSize(int x, int y)
{
	gridx = x;
	gridy = y;

	for (int col = 0; col < GRID_MAX; ++col)
	{
		for (int row = 0; row < GRID_MAX; ++row)
		{
			PlayboardItem* item = itemArray[row][col];
			item->setVisible(false);
		}
	}

	resetPlayboard();

	Size itemSize = PlayboardItem::getSize();

	Size size((float)gridx * (itemSize.width + DIST_X), (float)gridy * (itemSize.height + DIST_Y));

	setContentSize(size);
}

Vec2 Playboard::getGridMaxSize()
{
	int x = GRID_MAX;
	int y = GRID_MAX;

	return Vec2(x, y);
}

void Playboard::createItems()
{
	Vec2 grid = getGridMaxSize();

	Size itemSize = PlayboardItem::getSize();

	for (int col = 0; col < GRID_MAX; ++col)
	{
		for (int row = 0; row < GRID_MAX; ++row)
		{
			PlayboardItem* item = PlayboardItem::create();

			item->setVisible(false);

			item->setIndex(row, col);

			float x = itemSize.width / 2 + row * (itemSize.width + DIST_X);

			float y = itemSize.height / 2 + col * (itemSize.height + DIST_Y);

			item->setPosition(x, y);

			menu->addChild(item);

			itemArray[row][col] = item;
		}
	}
}

class PbItemState
{
public:
	PbItemState() : st(0), row(0), col(0) {}
	int st; // 1 - live, 2 - dead
	int row;
	int col;
};

bool Playboard::updatePlayboard()
{
	//int live0 = 0;
	//int dead0 = 0;

	std::vector<PbItemState> states;

	for (int col = 0; col < gridy; ++col)
	{
		for (int row = 0; row < gridx; ++row)
		{
			PlayboardItem* item = itemArray[row][col];

			//CCLOG("Playboard::updatePlayboard(0) [%d,%d] vs [%d,%d]- IN", row, col, item->getIndex().getRow(), item->getIndex().getCol());

			int itemStates[8] = { 0 }; // 0 - doesn't exist, 1 - dead, 2 - live

			if ((row + 1) >= 0 && (row + 1) < gridx)
			{
				PlayboardItem* pi = itemArray[row + 1][col];
				GridIndex index = pi->getIndex();
				PlayboardItem::State state = pi->getState();
				itemStates[0] = state == PlayboardItem::Live ? 1 : 2;
				//CCLOG("Playboard::updatePlayboard(1) [%d,%d]-%d", index.getRow(), index.getCol(), state);

				if ((col + 1) >= 0 && (col + 1) < gridy)
				{
					PlayboardItem* pi = itemArray[row + 1][col + 1];
					GridIndex index = pi->getIndex();
					PlayboardItem::State state = pi->getState();
					itemStates[1] = state == PlayboardItem::Live ? 1 : 2;
					//CCLOG("Playboard::updatePlayboard(2) [%d,%d]-%d", index.getRow(), index.getCol(), state);
				}

				if ((col - 1) >= 0 && (col - 1) < gridy)
				{
					PlayboardItem* pi = itemArray[row + 1][col - 1];
					GridIndex index = pi->getIndex();
					PlayboardItem::State state = pi->getState();
					itemStates[2] = state == PlayboardItem::Live ? 1 : 2;
					//CCLOG("Playboard::updatePlayboard(3) [%d,%d]-%d", index.getRow(), index.getCol(), state);
				}
			}

			if ((row - 1) >= 0 && (row - 1) < gridx)
			{
				PlayboardItem* pi = itemArray[row - 1][col];
				GridIndex index = pi->getIndex();
				PlayboardItem::State state = pi->getState();
				itemStates[3] = state == PlayboardItem::Live ? 1 : 2;
				//CCLOG("Playboard::updatePlayboard(4) [%d,%d]-%d", index.getRow(), index.getCol(), state);

				if ((col + 1) >= 0 && (col + 1) < gridy)
				{
					PlayboardItem* pi = itemArray[row - 1][col + 1];
					GridIndex index = pi->getIndex();
					PlayboardItem::State state = pi->getState();
					itemStates[4] = state == PlayboardItem::Live ? 1 : 2;
					//CCLOG("Playboard::updatePlayboard(5) [%d,%d]-%d", index.getRow(), index.getCol(), state);
				}

				if ((col - 1) >= 0 && (col - 1) < gridy)
				{
					PlayboardItem* pi = itemArray[row - 1][col - 1];
					GridIndex index = pi->getIndex();
					PlayboardItem::State state = pi->getState();
					itemStates[5] = state == PlayboardItem::Live ? 1 : 2;
					//CCLOG("Playboard::updatePlayboard(6) [%d,%d]-%d", index.getRow(), index.getCol(), state);
				}
			}

			if ((col + 1) >= 0 && (col + 1) < gridy)
			{
				PlayboardItem* pi = itemArray[row ][col + 1];
				GridIndex index = pi->getIndex();
				PlayboardItem::State state = pi->getState();
				itemStates[6] = state == PlayboardItem::Live ? 1 : 2;
				//CCLOG("Playboard::updatePlayboard(7) [%d,%d]-%d", index.getRow(), index.getCol(), state);
			}

			if ((col - 1) >= 0 && (col - 1) < gridy)
			{
				PlayboardItem* pi = itemArray[row][col - 1];
				GridIndex index = pi->getIndex();
				PlayboardItem::State state = pi->getState();
				itemStates[7] = state == PlayboardItem::Live ? 1 : 2;
				//CCLOG("Playboard::updatePlayboard(8) [%d,%d]-%d", index.getRow(), index.getCol(), state);
			}

			int live = 0;
			int dead = 0;

			for (int i = 0; i < 8; ++i)
			{
				if (itemStates[i] == 1)
					++live;
				else if (itemStates[i] == 2)
					++dead;
			}

			PlayboardItem::State state = item->getState();

			if (state == PlayboardItem::State::Live)
			{
				//++live0;

				if (live < 2 || live > 3)
				{
					//item->setState(PlayboardItem::State::Dead);
					PbItemState its;
					its.row = row;
					its.col = col;
					its.st = PlayboardItem::State::Dead;
					states.push_back(its);
				}
			}
			else if (state == PlayboardItem::State::Dead)
			{
				//++dead0;

				if (live == 3)
				{
					//item->setState(PlayboardItem::State::Live);
					PbItemState its;
					its.row = row;
					its.col = col;
					its.st = PlayboardItem::State::Live;
					states.push_back(its);
				}
			}
		}
	}

	// update states
	for (std::vector<PbItemState>::iterator it = states.begin(); it != states.end(); ++it)
	{
		PbItemState its = *it;

		//CCLOG("Playboard::updatePlayboard() [%d,%d]-%d", its.row, its.col, its.st);

		if (its.st == 1 || its.st == 2)
		{
			PlayboardItem::State state = its.st == 1 ? PlayboardItem::State::Live : PlayboardItem::State::Dead;

			itemArray[its.row][its.col]->setState(state);
		}
	}

	// game over
	int live1 = 0;
	int dead1 = 0;

	for (int col = 0; col < gridy; ++col)
	{
		for (int row = 0; row < gridx; ++row)
		{
			PlayboardItem* item = itemArray[row][col];

			if (item->getState() == PlayboardItem::State::Live)
				++live1;
			else if (item->getState() == PlayboardItem::State::Dead)
				++dead1;
		}
	}

	bool gameover = false;

	if (live1 == gridx * gridy || dead1 == gridx * gridy/* || (live1 == live0 && dead1 == dead0)*/)
	{
		gameover = true;
	}

	//CCLOG("Playboard::updatePlayboard() gameover - %d ", gameover);

	return gameover;
}
