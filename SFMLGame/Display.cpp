#include "Display.h"

#include <memory>

namespace Display
{
	std::unique_ptr<sf::RenderWindow> window;

	void init(int framerate, int width, int height, std::string title)
	{
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
		window->setFramerateLimit(framerate);
	}

	void clear()
	{
		window->clear();
	}

	void draw(const sf::Drawable & drawable)
	{
		window->draw(drawable);
	}

	void display()
	{
		window->display();
	}
}
