#pragma once

#include <memory>
#include <stack>
#include <Box2D\Box2D.h>

#include "resmgr\ResourceManager.h"
#include "entity\Entity.h"

class Application
{
public:
	Application(int frameCap, int updateCap);

	void runLoop();

private:
	int updateRate;

	b2World* world;

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	Entity* groundBody;
	Entity* dynamicBody;
};
