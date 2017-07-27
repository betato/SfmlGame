#pragma once

#include <memory>
#include <stack>
#include <Box2D\Box2D.h>

#include "entity\Entity.h"
#include "states\GameState.h"

class Application
{
public:
	Application(int frameCap, int updateCap);

	void pushState(std::unique_ptr<State::GameState> state);
	void popState();
	void changeState(std::unique_ptr<State::GameState> state);

	void runLoop();

private:
	int updateRate;

	std::stack<std::unique_ptr<State::GameState>> states;

	b2World* world;

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	Entity* groundBody;
	Entity* dynamicBody;
};
