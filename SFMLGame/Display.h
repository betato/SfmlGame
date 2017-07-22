#pragma once

#include<SFML\Graphics.hpp>

namespace Display
{
	void init(int framerate, int width, int height, std::string title);
	
	void clear();
	void draw(const sf::Drawable& drawable);
	void display();

	void checkEvents();
	bool isOpen();
}
