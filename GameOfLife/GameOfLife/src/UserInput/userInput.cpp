#include "userInput.h"
#include "../Window/window.h"

int UserInput::mousePosX{};
int UserInput::mousePosY{};

bool UserInput::leftMouseButton{};
bool UserInput::rightMouseButton{};

UserInput::UserInput()
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

void UserInput::processInput()
{
	ALLEGRO_EVENT event;
	if(!al_is_event_queue_empty(this->eventQueue))
	{
		ALLEGRO_MOUSE_STATE* mouseState;

		al_get_next_event(this->eventQueue, &event);
		switch (event.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			al_get_mouse_state(mouseState);
			if(mouseState->buttons & 1)
			{
				leftMouseButton = true;
			}
			else if(mouseState->buttons & 2)
			{
				rightMouseButton = true;
			}
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			al_get_mouse_state(mouseState);
			if (mouseState->buttons ^ 1)
			{
				leftMouseButton = false;
			}
			else if (mouseState->buttons ^ 2)
			{
				rightMouseButton = false;
			}
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			al_get_mouse_state(mouseState);
			mousePosX = mouseState->x;
			mousePosY = mouseState->y;
			break;
		}
	}
}

void UserInput::getMousePosition(int& x, int& y)
{
	x = mousePosX;
	y = mousePosY;
}

bool UserInput::isLeftMouseButtonClicked()
{
	return leftMouseButton;
}

bool UserInput::isRightMouseButtonClicked()
{
	return rightMouseButton;
}

void UserInput::init()
{
	this->eventQueue = al_create_event_queue();
	al_register_event_source(this->eventQueue, al_get_mouse_event_source());
	al_register_event_source(this->eventQueue, al_get_keyboard_event_source());
}
