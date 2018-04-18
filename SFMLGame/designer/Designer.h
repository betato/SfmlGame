#pragma once

#include <SFML\Graphics.hpp>

#include "Triangulator.h"

class Designer
{
public:
	void addPoint(sf::Vector2f point);
	void selectPoint(sf::Vector2f point);
	void deselectAll();
	void selectBox(sf::Vector2f p1, sf::Vector2f p2);
	void removePoints();
	void movePoints(sf::Vector2f delta);

	sf::VertexArray calcTriangles();
	void clear();

	sf::VertexArray getOutline();

private:
	std::vector<sf::Vector2f> outline;
	std::vector<bool> selected;

	bool intersecting(sf::Vector2f line1p1, sf::Vector2f line1p2, sf::Vector2f line2p1, sf::Vector2f line2p2);
	Triangulator triangulator;
};
