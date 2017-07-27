#pragma once

#include "GameState.h"

namespace State
{
	class Running : public GameState
	{
	public:
		Running(Application& application);

		void input() override;
		void update() override;
		void draw() override;
	private:

	};
}