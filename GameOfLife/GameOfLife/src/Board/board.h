#pragma once
#include <vector>

class Board
{
public:
	Board(int width, int height, bool withBorder);
	~Board();

	void update();
private:
	int width, height;
	bool withBorder;

	bool** board;

};

