#pragma once

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

namespace FileIO
{
	bool readText(vector<string>& text, string path);
	void writeText(vector<string> text, string path);

	bool readEntity(sf::VertexArray& vertices, sf::Vector2u textureSize, string path);
	bool readPhysics(b2PolygonShape& shape, string path);
	void writeEntity(sf::VertexArray vertices, sf::Vector2u textureSize, string path);
	void writePhysics(sf::VertexArray shape, string path);
}
