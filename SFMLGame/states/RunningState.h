#pragma once

#include <Box2D\Box2D.h>

#include "..\entity\Entity.h"
#include "GameState.h"
#include "..\Grid.h"

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

		sf::VertexArray entityOutline;
		Grid grid = Grid(1280, 720, 10, 10);;
		Designer designer;

		bool mouseHeld = false;
		sf::Vector2f mouseStart;
		sf::Vector2f mouseEnd;

		std::vector<sf::Vector2f> outline;

		sf::VertexArray triVerts;

		bool intersecting(sf::Vector2f line1p1, sf::Vector2f line1p2, sf::Vector2f line2p1, sf::Vector2f line2p2);
		void addPoint(sf::Vector2f point);

		sf::VertexArray triangulate(std::vector<sf::Vector2f>& shape);

		bool getOrient(sf::Vector2f& a, sf::Vector2f& b, sf::Vector2f& c);
		bool inTriangle(const sf::Vector2f& pt, const sf::Vector2f& v1, const sf::Vector2f& v2, const sf::Vector2f& v3);
		float sign(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);

		void mousePressed(const sf::Event& events);
		void mouseMoved(const sf::Event& events);
		void keyPressed(const sf::Event& events);
	};
}
