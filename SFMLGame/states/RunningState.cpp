#include "RunningState.h"

#include <vector>
#include <iostream>

#include "..\Display.h"
#include "..\FileLoader.h"

using namespace std;

namespace State
{
	Running::Running(Application & application) : GameState(application)
	{
		world = new b2World(b2Vec2(0.0f, -10.0f));

		std::vector<std::string> fileText;
		FileIO::readText(fileText, "res/oct.txt");
		
		// Test print file
		vector<string>::iterator it;
		for (it = fileText.begin(); it < fileText.end(); it++) {
			cout << *it << endl;
		}

		// Ground box
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(10.0f, -20.0f);

		b2PolygonShape groundBox;
		groundBox.SetAsBox(8.0f, 2.0f);

		b2FixtureDef groundFixtureDef;
		groundFixtureDef.shape = &groundBox;

		groundBody = new Entity(world, &groundBodyDef, &groundFixtureDef);

		// Physik box
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(10.0f, 0.0f);

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f, 1.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		dynamicBody = new Entity(world, &bodyDef, &fixtureDef);

		dynamicBody->setTexture(&ResourceManager::get().getTexture(TextureName::Test));
		groundBody->setTexture(&ResourceManager::get().getTexture(TextureName::Test));
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
