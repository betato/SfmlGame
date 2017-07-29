#include "RunningState.h"

#include <vector>

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
