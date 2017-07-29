#include "RunningState.h"

#include <vector>

#include "..\Display.h"
#include "..\FileLoader.h"

namespace State
{
	Running::Running(Application & application) : GameState(application)
	{
		world = new b2World(b2Vec2(0.0f, -10.0f));

		std::vector<sf::Vector2f> verticies;
		std::vector<sf::Vector2f> texCoords;
		FileIO::readEntity(verticies, texCoords, "res/oct.txt");

		b2PolygonShape shape;
		FileIO::readPhysics(shape, "res/phys.txt");

		// Ground box
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(10.0f, -20.0f);

		b2PolygonShape groundBox;
		groundBox.SetAsBox(8.0f, 2.0f);

		b2FixtureDef groundFixtureDef;
		groundFixtureDef.shape = &shape;

		groundBody = new Entity(world, &groundBodyDef, &groundFixtureDef);

		// Physik box
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(13.0f, 0.0f);

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f, 1.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		dynamicBody = new Entity(world, &bodyDef, &fixtureDef);

		dynamicBody->setTexture(&ResourceManager::get().getTexture(TextureName::Test));
		dynamicBody->setShape(verticies);
		dynamicBody->setTextureCoords(texCoords);

		groundBody->setTexture(&ResourceManager::get().getTexture(TextureName::Test));
		groundBody->setShape(verticies);
		groundBody->setTextureCoords(texCoords);
	}

	void Running::input(const sf::Event& events)
	{

	}

	void Running::update()
	{
		world->Step(timeStep, velocityIterations, positionIterations);
	}

	void Running::draw()
	{
		Display::draw(*groundBody);
		Display::draw(*dynamicBody);
	}
}
