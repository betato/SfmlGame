#include "Triangulator.h"

sf::VertexArray Triangulator::triangulate(std::vector<sf::Vector2f> shape)
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

bool Triangulator::getOrient(sf::Vector2f& a, sf::Vector2f& b, sf::Vector2f& c)
{
	// Return true if counter clockwise, otherwise false
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y) > 0;
}

bool Triangulator::inTriangle(const sf::Vector2f& p, const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c)
{
	// Determine if point p is inside triangle abc
	bool ba = sign(p, a, b) < 0.0f;
	bool bb = sign(p, b, c) < 0.0f;
	bool bc = sign(p, c, a) < 0.0f;

	return ba == bb && bb == bc;
}

float Triangulator::sign(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
	return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
}
