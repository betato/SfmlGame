#include "Display.h"

#include <memory>

namespace Display
{
	std::unique_ptr<sf::RenderWindow> window;

	void init(int framerate, int width, int height, std::string title)
	{
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
		window->setKeyRepeatEnabled(false);
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
	
	void checkEvents(State::GameState& gameState)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			// Sent game events
			gameState.input(event);
			// Check for close
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}
	}

	bool isOpen()
	{
		return window->isOpen();
	}
}
