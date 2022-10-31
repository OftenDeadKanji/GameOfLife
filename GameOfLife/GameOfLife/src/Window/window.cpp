#include "window.h"

#include "allegro5/allegro_primitives.h"

AllegroInitFailException::AllegroInitFailException(std::string message)
	: message(std::move(message))
{}

const char* AllegroInitFailException::what() const
{
	return this->message.c_str();
}

Window::Window(int width, int height, std::string title)
	: width(width), height(height), title(std::move(title))
{
	this->initAllegro();
	this->createAllegroDisplay();
}

Window::~Window()
{
	al_destroy_display(this->display);
}

void Window::drawBoard(float deltaTime, const Board& board) const
{
	al_clear_to_color(al_map_rgb(10, 90, 100));


	float cellSize = this->cellSize * this->zoom;

	const int x0 = static_cast<int>(0.5 * (this->width - board.getWidth() * cellSize)) + this->translationX;
	const int x1 = x0 + board.getWidth() * cellSize;

	const int y0 = static_cast<int>(0.5 * (this->height - board.getHeight() * cellSize)) + this->translationY;
	const int y1 = y0 + board.getHeight() * cellSize;


	for (int i = 0; i < board.getWidth() + 1; ++i)
	{
		al_draw_line(x0 + i * cellSize, y0, x0 + i * cellSize, y0 + board.getHeight() * cellSize, al_map_rgb(50, 50, 50), 2);
	}
	for (int j = 0; j < board.getHeight() + 1; ++j)
	{
		al_draw_line(x0, y0 + j * cellSize, x0 + board.getWidth() * cellSize, y0 + j * cellSize, al_map_rgb(50, 50, 50), 2);
	}

	int x{}, y {};
	for (int i = 0; i < board.getWidth();++i)
	{
		for (int j = 0; j < board.getHeight();++j)
		{
			if (board(i, j))
			{
				al_draw_filled_rectangle(x0 + i * cellSize, y0 + j * cellSize, x0 + (i + 1) * cellSize, y0 + (j + 1) * cellSize, al_map_rgb(50, 150, 20));
			}
		}
	}

	al_flip_display();
}

void Window::moveBoard(float dx, float dy)
{
	this->translationX += dx * this->translationSpeed;
	this->translationY += dy * this->translationSpeed;
}

void Window::zoomInOut(float zoomChange)
{
	this->zoom += zoomChange;
}

void Window::setZoom(float zoom)
{
	this->zoom = zoom;
}

void Window::getBoardCellIndicesByMousePosition(int& x, int& y, int mouseX, int mouseY, const Board& board)
{
	float cellSize = this->cellSize * this->zoom;

	const int x0 = static_cast<int>(0.5 * (this->width - board.getWidth() * cellSize)) + this->translationX;
	const int x1 = x0 + board.getWidth() * cellSize;

	const int y0 = static_cast<int>(0.5 * (this->height - board.getHeight() * cellSize)) + this->translationY;
	const int y1 = y0 + board.getHeight() * cellSize;

	x = y = 0;
	for (int i = x0; i < x1; i += cellSize, ++x, y = 0)
	{
		if (mouseX >= i && mouseX <= (i + cellSize))
		{
			for (int j = y0; j < y1; j += cellSize, ++y)
			{
				if (mouseY >= j && mouseY <= (j + cellSize))
				{
					return;
				}
			}
		}
	}
	x = y = -1;
}

void Window::initAllegro()
{
	if (!al_init())
	{
		throw AllegroInitFailException("Allegro5 init failed.");
	}
	if (!al_init_primitives_addon())
	{
		throw AllegroInitFailException("Primitives addon init failed.");
	}
}

void Window::createAllegroDisplay()
{
	al_set_new_window_title(this->title.c_str());
	this->display = al_create_display(this->width, this->height);
}

