#include "StaticOctagon.h"

#include "..\FileLoader.h"
#include "..\resmgr\ResourceManager.h"

StaticOctagon::StaticOctagon(b2World * world) : Entity(world)
{
	// Set physics
	b2PolygonShape shape;
	FileIO::readPhysics(shape, "res/phys.txt");

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(10.0f, -20.0f);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(8.0f, 2.0f);

	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &shape;

	createBody(&groundBodyDef);
	addFixture(&groundFixtureDef);

	// Set graphics
	std::vector<sf::Vector2f> verticies;
	std::vector<sf::Vector2f> texCoords;
	FileIO::readEntity(verticies, texCoords, "res/oct.txt");

	setTexture(&ResourceManager::get().getTexture(TextureName::Test));
	setShape(verticies);
	setTextureCoords(texCoords);
}
