#include "Designer.h"

sf::VertexArray Designer::calcTriangles()
{
	int length = outline.size() - 1;
	deselectAll();
	bool linesIntersecting = false;

	// Check lines intersecting line between first and last points
	for (int i = 0; i < length; i++)
	{
		if (intersecting(outline[length], outline[0], outline[i], outline[i + 1]))
		{
			// Select intersecting lines
			selected[length] = true;
			selected[0] = true;
			selected[i] = true;
			selected[i + 1] = true;
			linesIntersecting = true;
		}
	}

	// Check all other lines
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (intersecting(outline[i], outline[i + 1], outline[j], outline[j + 1]))
			{
				// Select intersecting lines
				selected[i] = true;
				selected[i + 1] = true;
				selected[j] = true;
				selected[j + 1] = true;
				linesIntersecting = true;
			}
		}
	}

	// This does not currently select the 

	if (linesIntersecting)
	{
		return sf::VertexArray();
	}
	else
	{
		return triangulator.triangulate(outline);
	}
}

void Designer::clear()
{
	outline.clear();
	selected.clear();
}

sf::VertexArray Designer::getOutline()
{
	sf::VertexArray drawOutline;
	drawOutline.setPrimitiveType(sf::LinesStrip);
	for (int i = 0; i < outline.size(); i++)
	{
		drawOutline.append(outline[i]);
		if (selected[i])
		{
			drawOutline[i].color = sf::Color(255, 0, 0, 255);
		}
	}
	// Draw line as visual indicator of the full loop
	if (outline.size() > 0)
	{
		drawOutline.append(drawOutline[0]);
	}
	return drawOutline;
}


void Designer::addPoint(sf::Vector2f point)
{
	outline.push_back(point);
	selected.push_back(false);
}

void Designer::selectPoint(sf::Vector2f point)
{
	for (int i = 0; i < outline.size(); i++)
	{
		if (point == outline[i])
		{
			// Toggle selection
			selected[i] = !selected[i];
			return;
		}
	}
}

void Designer::deselectAll()
{
	for (auto it = selected.begin(); it < selected.end(); it++)
	{
		*it = false;
	}
}

void Designer::selectBox(sf::Vector2f p1, sf::Vector2f p2)
{
	if (p2.x > p1.x)
	{
		float swap = p1.x;
		p1.x = p2.x;
		p2.x = swap;
	}
	if (p2.y > p1.y)
	{
		float swap = p1.y;
		p1.y = p2.y;
		p2.y = swap;
	}

	for (int i = 0; i < outline.size(); i++)
	{
		selected[i] =
			p1.x >= outline[i].x && outline[i].x >= p2.x &&
			p1.y >= outline[i].y && outline[i].y >= p2.y;
	}
}

void Designer::removePoints()
{
	for (int i = outline.size() - 1; i >= 0; i--)
	{
		if (selected[i])
		{
			// Remove point
			outline.erase(outline.begin() + i);
			selected.erase(selected.begin() + i);
		}
	}
}

void Designer::movePoints(sf::Vector2f delta)
{
	for (int i = 0; i < outline.size(); i++)
	{
		if (selected[i])
		{
			// Move point
			outline[i] += delta;
		}
	}
}

bool Designer::intersecting(sf::Vector2f line1p1, sf::Vector2f line1p2, sf::Vector2f line2p1, sf::Vector2f line2p2)
{
	return (((line1p1.x - line2p1.x)*(line2p2.y - line2p1.y) - (line1p1.y - line2p1.y)*(line2p2.x - line2p1.x)) *
		((line1p2.x - line2p1.x)*(line2p2.y - line2p1.y) - (line1p2.y - line2p1.y)*(line2p2.x - line2p1.x)) < 0) &&
		(((line2p1.x - line1p1.x)*(line1p2.y - line1p1.y) - (line2p1.y - line1p1.y)*(line1p2.x - line1p1.x)) *
		((line2p2.x - line1p1.x)*(line1p2.y - line1p1.y) - (line2p2.y - line1p1.y)*(line1p2.x - line1p1.x)) < 0);
}
