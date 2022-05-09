#include "userInput.h"
#include "../Window/window.h"
#include "../../imgui/imgui_impl_allegro5.h"


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

	//ImGuiIO& io = ImGui::GetIO();

	while (!al_is_event_queue_empty(this->eventQueue))
	{
		al_get_next_event(this->eventQueue, &event);
		//ImGui_ImplAllegro5_ProcessEvent(&event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (mouseState.buttons & 1)
			{
				//io.AddMouseButtonEvent(1, true);
			}
			else if (mouseState.buttons & 2)
			{
				//io.AddMouseButtonEvent(2, true);
			}
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			if (mouseState.buttons ^ 1)
			{
				//io.AddMouseButtonEvent(1, false);
			}
			else if (mouseState.buttons ^ 2)
			{
				//io.AddMouseButtonEvent(2, false);
			}
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:

			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			shouldWindowClose = true;
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
		}
	}
	
	//if (!io.WantCaptureMouse)
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

	//this->processImGui();
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

void UserInput::processImGui()
{
	ImGui_ImplAllegro5_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Game of Life", nullptr);
	if (ImGui::Button("Start"))
	{
		this->board.start();
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		this->board.stop();
	}
	ImGui::SameLine();
	if (ImGui::Button("Restart"))
	{
		this->board.restart();
	}
	static float zoom{ 1.0f };
	ImGui::SliderFloat("##", &zoom, 1.0f, 10.0f);
	this->window.setZoom(zoom);

	ImGui::End();

	ImGui::Render();
}
