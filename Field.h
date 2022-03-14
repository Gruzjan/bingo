#include <vector>
#include "Cell.h"
#pragma once

class Field
{
public:
	std::vector<Cell> cells;
	Field();
	bool isGameOver();
	void checkCell(int x, int y);
};

