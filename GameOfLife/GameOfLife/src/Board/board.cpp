#include "board.h"

Board::Board(int width, int height, bool withBorder)
	: width(width), height(height), withBorder(withBorder)
{
	this->board = new bool* [this->width];
	for(int i = 0;i < this->width;++i)
	{
		this->board[i] = new bool[this->height];
	}
}

Board::~Board()
{
	for (int i = 0; i < this->width; ++i)
	{
		delete[] this->board;
	}
	delete[] this->board;
}
