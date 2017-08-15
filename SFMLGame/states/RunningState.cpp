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
			int roundX = ((events.mouseButton.x + 5) / 10) * 10;
			int roundY = ((events.mouseButton.y + 5) / 10) * 10;
			
			addPoint(sf::Vector2f(roundX, roundY));
		}

		if (events.key.code == sf::Keyboard::Space)
		{
			for (int i = 0; i < entityOutline.getVertexCount(); i++)
			{
				outline.push_back(entityOutline[i].position);
			}

			triVerts = triangulate(outline);
			int r;
			int g;
			int b;
			for (int i = 0; i < triVerts.getVertexCount(); i++)
			{
				if (i % 3 == 0)
				{
					r = (rand() % static_cast<int>(255));
					g = (rand() % static_cast<int>(255));
					b = (rand() % static_cast<int>(255));
				}
				triVerts[i].color = sf::Color(r, g, b, 255);
			}
			outline.clear();
		}
		if (events.key.code == sf::Keyboard::C)
		{
			triVerts.clear();
			entityOutline.clear();
			outline.clear();
		}
	}

	void Running::update()
	{
		world->Step(timeStep, velocityIterations, positionIterations);
	}

	void Running::draw()
	{
		Display::draw(grid);

		Display::draw(triVerts);

		for (int i = 0; i < entityOutline.getVertexCount(); i++)
		{
			point.setPosition(entityOutline[i].position - sf::Vector2f(point.getRadius(), point.getRadius()));
			Display::draw(point);
		}
		
		Display::draw(entityOutline);
		if (entityOutline.getVertexCount() > 1)
		{
			sf::VertexArray endLine;
			endLine.setPrimitiveType(sf::Lines);
			endLine.append(entityOutline[entityOutline.getVertexCount() - 1]);
			endLine.append(entityOutline[0]);
			Display::draw(endLine);
		}

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
		//for (int i = 0; i < length; i++)
		//{
		//	if (intersecting(entityOutline[i].position, entityOutline[i + 1].position, entityOutline[length].position, point))
		//	{
		//		// Lines intersect, don't add
		//		return;
		//	}
		//}
		entityOutline.append(point);
	}

	sf::VertexArray Running::triangulate(std::vector<sf::Vector2f>& shape)
	{
		sf::VertexArray triangles;
		triangles.setPrimitiveType(sf::PrimitiveType::Triangles);
		std::vector<int> reflex;

		// Already a triangle, return existing points
		if (shape.size() <= 3)
		{
			for each (sf::Vector2f v in shape)
			{
				triangles.append(v);
			}
			return triangles;
		}

		// Determine polygon point direction
		sf::Vector2f left = shape[0];
		int point = 0;

		// Get top left triangle as orientation base
		for (int i = 0; i < shape.size(); i++)
		{
			if (shape[i].x < left.x || (shape[i].x == left.x && shape[i].y < left.y))
			{
				point = i;
				left = shape[i];
			}
		}

		// Get triangle point direction
		bool orientation = getOrient(
			shape[(point > 0) ? point - 1 : shape.size() - 1],
			shape[point],
			shape[(point < shape.size() - 1) ? point + 1 : 0]
		);

		// Triangulate
		while (shape.size() >= 3)
		{
			reflex.clear();
			int eartip = -1;
			int index = -1;
			// Find an ear
			for (sf::Vector2f i : shape)
			{
				index++; 
				// Stop at first possible eartip
				if (eartip >= 0)
				{
					break;
				}
				 
				// Create triangle
				int prev = (index > 0) ? index - 1 : shape.size() - 1; // Previous point, if unavalible, use last one from loop
				int next = (index < shape.size() - 1) ? index + 1 : 0; // Next point, if unavailible, use first one from loop

				// Find relative orientation 
				if (getOrient(shape[prev], i, shape[next]) != orientation)
				{
					reflex.emplace_back(index);
					continue;
				}
				
				bool ear = true;

				// Check known reflex verticies first
				for (int j : reflex)
				{
					// Don't test self
					if (j == prev || j == next)
					{
						continue;
					}

					if (inTriangle(shape[j], shape[prev], i, shape[next]))
					{
						ear = false;
						break;
					}
				}

				// Check all other verticies as some may be reflex verticies
				for (auto it = shape.begin() + index + 1; it != shape.end(); it++)
				{
					sf::Vector2f vec = *it;

					// Don't test self
					if (vec == shape[prev] || vec == shape[next] || vec == shape[index])
					{
						continue;
					}

					if (inTriangle(vec, shape[prev], i, shape[next]))
					{
						ear = false;
						break;
					}
				}

				// Ear exists
				if (ear)
				{
					eartip = index;
				}
			}

			// Check if ear was found, otherwise break
			if (eartip < 0)
			{
				break;
			}

			// Create triangle
			triangles.append(shape[eartip > 0 ? eartip - 1 : shape.size() - 1]);
			triangles.append(shape[eartip]);
			triangles.append(shape[eartip < shape.size() - 1 ? eartip + 1 : 0]);

			// Clip ear
			shape.erase(std::find(shape.begin(), shape.end(), shape[eartip]));
		}

		return triangles;
	}

	bool Running::getOrient(sf::Vector2f& a, sf::Vector2f& b, sf::Vector2f& c)
	{
		// Return true if counter clockwise, otherwise false
		return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y) > 0;
	}

	bool Running::inTriangle(const sf::Vector2f& p, const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c)
	{
		// Determine if point p is inside triangle abc
		bool ba = sign(p, a, b) < 0.0f;
		bool bb = sign(p, b, c) < 0.0f;
		bool bc = sign(p, c, a) < 0.0f;

		return ba == bb && bb == bc;
	}

	float Running::sign(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
	{
		return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
	}
}
