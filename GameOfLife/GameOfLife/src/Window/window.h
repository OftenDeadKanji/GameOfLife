#pragma once
#include <allegro5/allegro5.h>
#include <string>
#include <exception>
#include "../Board/board.h"
#include "../UserInput/userInput.h"

class AllegroInitFailException
: public std::exception
{
public:
	explicit AllegroInitFailException(std::string message);

	[[nodiscard]] const char* what() const override;

private:
	std::string message;
};

class Window
{
	friend void UserInput::registerDisplayInput(const Window& window);
public:
	Window(int width, int height, std::string title);

	void drawBoard(const Board& board) const;
	void moveBoard(int dx, int dy);
	void zoomInOut(float zoomChange);
private:
	void initAllegro();
	void createAllegroDisplay();

	int width, height;
	std::string title;
	ALLEGRO_DISPLAY* display{};

	float zoom{ 1.0f }; //one cell -> one pixel?
	int translationX{}, translationY{};
};

