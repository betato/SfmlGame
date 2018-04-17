#include "Grid.h"

Grid::Grid(int width, int height, int spaceX, int spaceY) : Grid(width, height, spaceX, spaceY, sf::Color(115, 115, 115, 255)) { }

Grid::Grid(int width, int height, int spaceX, int spaceY, sf::Color colour)
{
	lines.setPrimitiveType(sf::Lines);

	for (int i = 0; i < width; i += spaceX)
	{
		lines.append(sf::Vertex(sf::Vector2f(i, 0), colour));
		lines.append(sf::Vertex(sf::Vector2f(i, height), colour));
	}

	for (int i = 0; i < height; i += spaceY)
	{
		lines.append(sf::Vertex(sf::Vector2f(0, i), colour));
		lines.append(sf::Vertex(sf::Vector2f(width, i), colour));
	}
}

void Grid::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(lines, states);
}
