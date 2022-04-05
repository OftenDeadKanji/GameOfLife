#pragma once
#include "allegro5/allegro5.h"

class Window;

class UserInput
{
public:
	UserInput();
	~UserInput();

	void registerDisplayInput(const Window& window);

	void processInput();

	static void getMousePosition(int& x, int& y);
	static bool isLeftMouseButtonClicked();
	static bool isRightMouseButtonClicked();
private:
	void init();

	ALLEGRO_EVENT_QUEUE* eventQueue{};

	static int mousePosX, mousePosY;
	static bool leftMouseButton, rightMouseButton;
};

