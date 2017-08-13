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

		entityOutline.setPrimitiveType(sf::LinesStrip);
		point = sf::CircleShape(4);

		sf::Color lineColour = sf::Color(115, 115, 115, 255);

		grid.setPrimitiveType(sf::Lines);
		for (int i = 0; i < 1280; i += 10)
		{
			grid.append(sf::Vertex(sf::Vector2f(i, 0), lineColour));
			grid.append(sf::Vertex(sf::Vector2f(i, 720), lineColour));
		}
		for (int i = 0; i < 720; i += 10)
		{
			grid.append(sf::Vertex(sf::Vector2f(0, i), lineColour));
			grid.append(sf::Vertex(sf::Vector2f(1280, i), lineColour));
		}
	}

	void Running::input(const sf::Event& events)
	{
		if (events.type == sf::Event::MouseButtonPressed) {
			std::cout << events.mouseButton.x << ", " << events.mouseButton.y;
			int roundX = ((events.mouseButton.x + 5) / 10) * 10;
			int roundY = ((events.mouseButton.y + 5) / 10) * 10;

			addPoint(sf::Vector2f(roundX, roundY));
		}
	}

	void Running::update()
	{
		world->Step(timeStep, velocityIterations, positionIterations);
	}

	void Running::draw()
	{
		Display::draw(grid);
		
		int length = entityOutline.getVertexCount();
		for (int i = 0; i < length; i++)
		{
			// point.setPosition(sf::Vector2f(entityOutline[i].position.x * 10 - point.getRadius(), entityOutline[i].position.y * 10 - point.getRadius()));
			point.setPosition(entityOutline[i].position - sf::Vector2f(point.getRadius(), point.getRadius()));
			Display::draw(point);
		}
		Display::draw(entityOutline);

		Display::draw(*groundBody);
		Display::draw(*dynamicBody);
	}

	bool Running::intersecting(sf::Vector2f line1p1, sf::Vector2f line1p2, sf::Vector2f line2p1, sf::Vector2f line2p2)
	{
		return (((line1p1.x - line2p1.x)*(line2p2.y - line2p1.y) - (line1p1.y - line2p1.y)*(line2p2.x - line2p1.x)) * ((line1p2.x - line2p1.x)*(line2p2.y - line2p1.y) - (line1p2.y - line2p1.y)*(line2p2.x - line2p1.x)) < 0) &&
			(((line2p1.x - line1p1.x)*(line1p2.y - line1p1.y) - (line2p1.y - line1p1.y)*(line1p2.x - line1p1.x)) * ((line2p2.x - line1p1.x)*(line1p2.y - line1p1.y) - (line2p2.y - line1p1.y)*(line1p2.x - line1p1.x)) < 0);
	}
	void Running::addPoint(sf::Vector2f point)
	{
		int length = entityOutline.getVertexCount() - 1;
		for (int i = 0; i < length; i++)
		{
			if (intersecting(entityOutline[i].position, entityOutline[i + 1].position, entityOutline[length].position, point))
			{
				// Lines intersect, don't add
				return;
			}
		}
		entityOutline.append(point);
	}
}
