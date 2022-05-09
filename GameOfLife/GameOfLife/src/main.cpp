#include <iostream>
#include <chrono>

#include "Window/window.h"
#include "Board/board.h"

void calculateDeltaTime(float& deltaTime, std::chrono::steady_clock::time_point& frameStart)
{
	deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - frameStart).count() * 0.000000001f;
	frameStart = std::chrono::steady_clock::now();
}

int main()
{
	std::cout << "Hello there!" << std::endl;

	Window window{ 1200, 1200, "Game of Life with OpenCL!" };
	try
	{
		Board board{ 50, 50, true };

		UserInput userInput(window, board);
		userInput.registerDisplayInput(window);

		float deltaTime = 0.0f;
		std::chrono::steady_clock::time_point frameStart = std::chrono::steady_clock::now();
		while (!userInput.isWindowCloseClicked())
		{
			calculateDeltaTime(deltaTime, frameStart);

			userInput.processInput(deltaTime);
			board.update(deltaTime);
			window.drawBoard(deltaTime, board);
		}
	}
	catch(BoardComputeProgramFailException& ex)
	{
		std::cout << ex.what() << std::endl;
		return -1;
	}
}
