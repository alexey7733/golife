#ifndef  _UTILS_H_
#define  _UTILS_H_

#include <string>

class Utils
{
public:
	static bool isEqual(float a, float b, float epsilon = 0.005f);
	static std::string intToString(int val);
};

// GridIndex
class GridIndex
{
public:

	GridIndex();

	GridIndex(int _row, int _col);

	void init(GridIndex i);
	void init(int r, int c);

	int getRow();
	int getCol();

	void setRow(int r);
	void setCol(int c);

private:

	int row;
	int col;
};

#endif // _UTILS_H_
