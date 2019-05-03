#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

class GameController
{
public:
	enum State
	{
		None = 0,
		Play,
		Over
	};
public:
	virtual ~GameController();
    static GameController* instance();
	void release();

	State getState();
	void setState(State s);

private:
	GameController();
	void init();

private:
	State state;
	static GameController* obj;
};

#endif // __GAMECONTROLLER_H__
