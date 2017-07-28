#pragma once

#include<SFML\Graphics.hpp>

#include "states\GameState.h"

namespace Display
{
	void init(int framerate, int width, int height, std::string title);
	
	void clear();
	void draw(const sf::Drawable& drawable);
	void display();

	void checkEvents(State::GameState& gameState);
	bool isOpen();
}
