#pragma once
#include "allegro5/allegro5.h"
#include "../Board/board.h"

class Window;

class UserInput
{
public:
	explicit UserInput(Window& window, Board& board);
	~UserInput();

	void registerDisplayInput(const Window& window);

	void processInput(float deltaTime);
	
	bool isWindowCloseClicked();
private:
	void init();

	Window& window;
	Board& board;

	ALLEGRO_EVENT_QUEUE* eventQueue{};
	bool shouldWindowClose;
};