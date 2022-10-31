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

	const char* what() const override;

private:
	std::string message;
};

class Window
{
	friend void UserInput::registerDisplayInput(const Window& window);
public:
	Window(int width, int height, std::string title);
	~Window();

	void drawBoard(float deltaTime, const Board& board) const;
	void moveBoard(float dx, float dy);

	void zoomInOut(float zoomChange);
	void setZoom(float zoom);

	void getBoardCellIndicesByMousePosition(int& x, int& y, int mouseX, int mouseY, const Board& board);
private:
	void initAllegro();
	void createAllegroDisplay();

	int width, height;
	std::string title;
	ALLEGRO_DISPLAY* display{};

	mutable float zoom{ 1.0f };

	float translationX{}, translationY{};
	float translationSpeed{ 100.0f };

	int cellSize{ 10 };
};

