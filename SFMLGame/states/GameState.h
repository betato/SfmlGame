#pragma once

#include "..\resmgr\ResourceManager.h"

class Application;

namespace State
{
	class GameState
	{
	public:
		GameState(Application& application);
		virtual void input() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

	protected:
		Application* application;
	};
}

