#include "StaticOctagon.h"

#include <iostream>

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
	const sf::Texture* texture = &ResourceManager::get().getTexture(TextureName::Test);

	sf::VertexArray vertices;
	FileIO::readEntity(vertices, texture->getSize(), "res/oct.txt");

	setTexture(texture);
	setShape(vertices);
}
