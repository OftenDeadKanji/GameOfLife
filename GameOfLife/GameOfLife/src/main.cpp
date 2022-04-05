#include <iostream>

#include "Window/window.h"
#include "Board/board.h"

int main()
{
	std::cout << "Hello there!" << std::endl;

	Window window{ 1600, 900, "Game of Life with OpenCL!" };
	Board board{ 300, 300, true };

	while(1)
	{
		window.drawBoard(board);
	}
}
