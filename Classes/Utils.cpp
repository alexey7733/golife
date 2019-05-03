#include "Utils.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////////////

static const int BUF_SIZE = 80;
static char buf[BUF_SIZE] = { 0 };

////////////////////////////////////////////////////////////////////////////////

// Utils
bool Utils::isEqual(float a, float b, float epsilon)
{
	bool res = fabs(a - b) < epsilon;

	return res;
}

std::string Utils::intToString(int val)
{
	char buf[11] = { 0 };

	unsigned int size = sizeof(buf);

	snprintf(buf, size, "%d", val);

	std::string res = buf;

	return res;
}


// GridIndex
GridIndex::GridIndex()
: row(0)
, col(0)
{
	//
}

GridIndex::GridIndex(int _row, int _col)
: row(_row)
, col(_col)
{
	//
}

void GridIndex::init(GridIndex i)
{
	row = i.row;
	col = i.col;
}

void GridIndex::init(int r, int c)
{
	row = r;
	col = c;
}

int GridIndex::getRow()
{
	return row;
}

int GridIndex::getCol()
{
	return col;
}

void GridIndex::setRow(int r)
{
	row = r;
}

void GridIndex::setCol(int c)
{
	col = c;
}
