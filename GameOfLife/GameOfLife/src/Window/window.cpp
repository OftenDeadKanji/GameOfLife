#include "window.h"

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

void Window::drawBoard(const Board& board) const
{
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();
}

void Window::moveBoard(int dx, int dy)
{
	this->translationX += dx;
	this->translationY += dy;
}

void Window::zoomInOut(float zoomChange)
{
	this->zoom += zoomChange;
}

void Window::initAllegro()
{
	if(!al_init())
	{
		throw AllegroInitFailException("Allegro5 init failed.");
	}
}

void Window::createAllegroDisplay()
{
	al_set_new_window_title(this->title.c_str());
	this->display = al_create_display(this->width, this->height);
}
