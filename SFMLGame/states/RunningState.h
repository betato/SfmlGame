#pragma once

#include <Box2D\Box2D.h>

#include "..\entity\Entity.h"
#include "GameState.h"

namespace State
{
	class Running : public GameState
	{
	public:
		Running(Application& application);

		void input(const sf::Event& events) override;
		void update() override;
		void draw() override;
	private:
		b2World* world;

		float32 timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 8;
		int32 positionIterations = 3;

		Entity* groundBody;
		Entity* dynamicBody;
	};
}