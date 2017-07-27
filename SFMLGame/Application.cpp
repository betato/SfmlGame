#include "Application.h"

#include <iostream>

#include "Display.h"
#include "resmgr\ResourceManager.h"

Application::Application(int frameCap, int updateCap)
{
	Display::init(frameCap, 1280, 720, "Window");
	updateRate = updateCap;
}

void Application::runLoop()
{
	world = new b2World(b2Vec2(0.0f, -10.0f));

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

	sf::Time delta = sf::Time::Zero;
	sf::Time updateTime = sf::microseconds(1000000 / updateRate);
	bool render = false;

	int frameCount = 0;
	int updateCount = 0;

	int fps = 0;
	int ups = 0;

	sf::Clock updateClock;
	sf::Clock counterClock;

	while (Display::isOpen())
	{
		if (counterClock.getElapsedTime() >= sf::seconds(1)) {
			fps = frameCount;
			ups = updateCount;
			frameCount = 0;
			updateCount = 0;

			std::cout << " FPS: " << fps;
			std::cout << " UPS: " << ups;

			counterClock.restart();
		}

		while (delta >= updateTime) {
			delta -= updateTime;
			updateCount++;
			render = true;

			// Update
			world->Step(timeStep, velocityIterations, positionIterations);
			Display::checkEvents();
		}

		if (render) {
			frameCount++;

			Display::clear();		// Clear

			Display::draw(*groundBody); // Draw
			Display::draw(*dynamicBody);

			Display::display();		// Display
		}

		delta += updateClock.restart();
	}
}
