#pragma once

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

namespace FileIO
{
	bool readText(vector<string>& file, string path);
	bool readEntity(vector<sf::Vector2f>& verticies, vector<sf::Vector2f>& texCoords, string path);
	bool readPhysics(b2PolygonShape& shape, string path);
}