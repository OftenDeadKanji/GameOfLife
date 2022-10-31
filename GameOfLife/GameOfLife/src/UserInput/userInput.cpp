#include "userInput.h"
#include "../Window/window.h"


UserInput::UserInput(Window& window, Board& board)
	: window(window), board(board)
{
	al_install_keyboard();
	al_install_mouse();

	this->init();
}

UserInput::~UserInput()
{
	al_destroy_event_queue(this->eventQueue);
}

void UserInput::registerDisplayInput(const Window& window)
{
	al_register_event_source(this->eventQueue, al_get_display_event_source(window.display));
}

void UserInput::processInput(float deltaTime)
{
	ALLEGRO_EVENT event;

	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	ALLEGRO_KEYBOARD_STATE keyboardState;
	al_get_keyboard_state(&keyboardState);


	while (!al_is_event_queue_empty(this->eventQueue))
	{
		al_get_next_event(this->eventQueue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			shouldWindowClose = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if(al_key_down(&keyboardState, ALLEGRO_KEY_SPACE))
			{
				if(board.isUpdating())
				{
					board.stop();
				}
				else
				{
					board.start();
				}
			}
			break;
		}
	}
	
	{
		if (!this->board.isUpdating())
		{
			if (mouseState.buttons & 1)
			{
				int i{}, j{};
				window.getBoardCellIndicesByMousePosition(i, j, mouseState.x, mouseState.y, this->board);
				if (i != -1 && j != -1)
				{
					this->board(i, j) = 1;
				}
			}
			else if (mouseState.buttons & 2)
			{
				int i{}, j{};
				window.getBoardCellIndicesByMousePosition(i, j, mouseState.x, mouseState.y, this->board);
				if (i != -1 && j != -1)
				{
					this->board(i, j) = 0;
				}
			}
		}
	}

	float moveInX{}, moveInY{};
	if (al_key_down(&keyboardState, ALLEGRO_KEY_W))
	{
		moveInY -= deltaTime;
	}
	if (al_key_down(&keyboardState, ALLEGRO_KEY_S))
	{
		moveInY += deltaTime;
	}
	if (al_key_down(&keyboardState, ALLEGRO_KEY_D))
	{
		moveInX += deltaTime;
	}
	if (al_key_down(&keyboardState, ALLEGRO_KEY_A))
	{
		moveInX -= deltaTime;
	}
	this->window.moveBoard(moveInX, moveInY);

}

bool UserInput::isWindowCloseClicked()
{
	return shouldWindowClose;
}

void UserInput::init()
{
	this->eventQueue = al_create_event_queue();
	al_register_event_source(this->eventQueue, al_get_mouse_event_source());
	al_register_event_source(this->eventQueue, al_get_keyboard_event_source());
}
