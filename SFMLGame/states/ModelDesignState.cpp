#include "ModelDesignState.h"

#include "..\Display.h"
#include "..\FileLoader.h"

namespace State
{
	ModelDesign::ModelDesign(Application & application) : GameState(application)
	{
		sf::Vector2u windowSize = Display::getSize();
		designerView = sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
		designerView.setViewport(sf::FloatRect(0, 0, 1, 1));
		//designerView.zoom(0.125);
		Display::setView(designerView);
	}

	void ModelDesign::input(const sf::Event& events)
	{
		switch (events.type)
		{
		case sf::Event::MouseButtonPressed:
			mousePressed(events);
			break;
		case sf::Event::MouseButtonReleased:
			mouseReleased(events);
			break;
		case sf::Event::MouseMoved:
			mouseMoved(events);
			break; 
		case sf::Event::MouseWheelScrolled:
				mouseScrolled(events);
				break;
		case sf::Event::KeyPressed:
			keyPressed(events);
			break;
		case sf::Event::KeyReleased:
			keyReleased(events);
			break;
		case sf::Event::Resized:
			windowResized(events);
		}
	}

	void ModelDesign::update()
	{
		
	}

	void ModelDesign::draw()
	{
		Display::draw(grid);

		Display::draw(triangulation);
		// Draw circles on outline verticies
		sf::VertexArray outline = designer.getOutline();
		Display::draw(outline);

		sf::CircleShape circle = sf::CircleShape(4);
		for (int i = 0; i < outline.getVertexCount(); i++)
		{
			circle.setPosition(outline[i].position - sf::Vector2f(4, 4));
			circle.setFillColor(outline[i].color);
			Display::draw(circle);
		}

		if (boxSelecting)
		{
			sf::RectangleShape selectionRect = sf::RectangleShape(mouseEnd - mouseStart);
			selectionRect.setPosition(mouseStart);
			selectionRect.setFillColor(sf::Color(255, 0, 0, 50));
			Display::draw(selectionRect);
		}
	}

	void ModelDesign::mousePressed(const sf::Event & events)
	{
		sf::Vector2f mouse = Display::getMappedMouse();
		int roundX = (((int)mouse.x + 5) / 10) * 10;
		int roundY = (((int)mouse.y + 5) / 10) * 10;
		if (events.mouseButton.button == sf::Mouse::Left)
		{
			// Add point
			designer.addPoint(sf::Vector2f(roundX, roundY));
		}
		else if (events.mouseButton.button == sf::Mouse::Right)
		{
			// Select Point
			designer.selectPoint(sf::Vector2f(roundX, roundY));

			boxSelecting = true;
			mouseStart = sf::Vector2f(roundX, roundY);
			mouseEnd = sf::Vector2f(roundX, roundY);
		}

		if (events.mouseButton.button == sf::Mouse::Middle)
		{
			moveStart = sf::Vector2f(roundX, roundY);
			moving = true;
		}
	}

	void ModelDesign::mouseReleased(const sf::Event & events)
	{
		if (events.mouseButton.button == sf::Mouse::Right)
		{
			boxSelecting = false;
		}

		if (events.mouseButton.button == sf::Mouse::Middle)
		{
			moving = false;
		}
	}

	void ModelDesign::mouseMoved(const sf::Event & events)
	{
		sf::Vector2f mouse = Display::getMappedMouse();
		int roundX = ((mouse.x + 5) / 10) * 10;
		int roundY = ((mouse.y + 5) / 10) * 10;
		if (boxSelecting)
		{
			mouseEnd = sf::Vector2f(roundX, roundY);
			designer.selectBox(mouseStart, mouseEnd);
		}

		if (moving)
		{
			designer.movePoints(sf::Vector2f(roundX, roundY) - moveStart);
			moveStart = sf::Vector2f(roundX, roundY);
		}
	}

	void ModelDesign::mouseScrolled(const sf::Event & events)
	{
		// Zoom
		Display::setView(designerView);
		sf::Vector2f beforeCoords = Display::getMappedMouse();
		float scroll = -events.mouseWheelScroll.delta;
		if (scroll > 0)
		{
			// Zoom out
			designerView.zoom((float)(std::fmin(scroll, 6) / 20) + 1);
		}
		else
		{
			// Zoom in
			designerView.zoom((float)(std::fmax(scroll, -6) / 20) + 1);
		}
		Display::setView(designerView);
		sf::Vector2f afterCoords = Display::getMappedMouse();
		designerView.move(beforeCoords - afterCoords);
	}

	void ModelDesign::keyPressed(const sf::Event & events)
	{
		if (events.key.code == sf::Keyboard::Space)
		{
			triangulation = designer.calcTriangles();
			int r;
			int g;
			int b;
			for (int i = 0; i < triangulation.getVertexCount(); i++)
			{
				if (i % 3 == 0)
				{
					r = (rand() % static_cast<int>(255));
					g = (rand() % static_cast<int>(255));
					b = (rand() % static_cast<int>(255));
				}
				triangulation[i].color = sf::Color(r, g, b, 255);
			}
		}

		if (events.key.code == sf::Keyboard::C)
		{
			designer.clear();
			triangulation.clear();
		}

		if (events.key.code == sf::Keyboard::Delete)
		{
			designer.removePoints();
		}

		if (events.key.code == sf::Keyboard::W)
		{
			// Write to file
			FileIO::writePhysics(triangulation, "res/testfile.txt");
		}

		if (events.key.code == sf::Keyboard::Z)
		{
			// Reset zoom
			sf::Vector2u windowSize = Display::getSize();
			designerView.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
			designerView.zoom(1);
			Display::setView(designerView);
		}
	}

	void ModelDesign::keyReleased(const sf::Event & events)
	{
		
	}

	void ModelDesign::windowResized(const sf::Event & events)
	{

	}
}