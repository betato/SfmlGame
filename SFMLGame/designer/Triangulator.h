#pragma once

#include <SFML\Graphics.hpp>

class Triangulator
{
public:
	sf::VertexArray triangulate(std::vector<sf::Vector2f> shape);

private:
	bool getOrient(sf::Vector2f& a, sf::Vector2f& b, sf::Vector2f& c);
	bool inTriangle(const sf::Vector2f& pt, const sf::Vector2f& v1, const sf::Vector2f& v2, const sf::Vector2f& v3);
	float sign(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);
};
