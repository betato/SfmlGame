#include "RunningState.h"

#include <vector>
#include <iostream>

#include "..\Display.h"
#include "..\entity\StaticOctagon.h"
#include "..\entity\DynamicOctagon.h"

namespace State
{
	Running::Running(Application & application) : GameState(application)
	{
		world = new b2World(b2Vec2(0.0f, -10.0f));

		groundBody = new StaticOctagon(world);
		dynamicBody = new DynamicOctagon(world);
	}

	void Running::input(const sf::Event& events)
	{
		switch (events.type)
		{
		case sf::Event::MouseButtonPressed:
			mousePressed(events);
			break;
		case sf::Event::KeyPressed:
			keyPressed(events);
			break;
		case sf::Event::MouseMoved:
			mouseMoved(events);
		}
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

	void Running::mousePressed(const sf::Event & events)
	{
		
	}

	void Running::mouseMoved(const sf::Event & events)
	{
		
	}

	void Running::keyPressed(const sf::Event & events)
	{
		
	}
}
