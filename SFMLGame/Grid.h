#pragma once

#include <SFML\Graphics.hpp>

class Grid : public sf::Drawable
{
public:
	Grid(int width, int height, int spaceX, int spaceY);
	Grid(int width, int height, int spaceX, int spaceY, sf::Color colour);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::VertexArray lines;
};
