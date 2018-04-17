#pragma once

#include "..\designer\Designer.h"
#include "GameState.h"
#include "..\Grid.h"

namespace State
{
	class ModelDesign : public GameState
	{
	public:
		ModelDesign(Application& application);

		void input(const sf::Event& events) override;
		void update() override;
		void draw() override;
	private:

		Grid grid = Grid(1280, 720, 10, 10);
		Designer designer;

		bool boxSelecting = false;
		sf::Vector2f mouseStart;
		sf::Vector2f mouseEnd;

		bool moving = false;
		sf::Vector2f moveStart;

		sf::VertexArray triangulation;

		void mousePressed(const sf::Event& events);
		void mouseReleased(const sf::Event& events);
		void mouseMoved(const sf::Event& events);

		void keyPressed(const sf::Event& events);
		void keyReleased(const sf::Event& events);

		void windowResized(const sf::Event& events);
	};
}