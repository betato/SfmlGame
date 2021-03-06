#include "DynamicOctagon.h"

#include "..\FileLoader.h"
#include "..\resmgr\ResourceManager.h"

DynamicOctagon::DynamicOctagon(b2World * world) : Entity(world)
{
	// Set physics
	b2PolygonShape shape;
	FileIO::readPhysics(shape, "res/phys.txt");

	// Ground box
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(13.0f, 0.0f);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(8.0f, 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	createBody(&bodyDef);
	addFixture(&fixtureDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	
	// Set graphics
	const sf::Texture* texture = &ResourceManager::get().getTexture(TextureName::Test);

	sf::VertexArray vertices;
	FileIO::readEntity(vertices, texture->getSize(), "res/oct.txt");

	setTexture(texture);
	setShape(vertices);
}
