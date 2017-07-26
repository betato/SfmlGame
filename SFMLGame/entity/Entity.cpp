#include "Entity.h"

static const float radToDeg = 180.0f / 3.141592f;

Entity::Entity(b2World* world, b2BodyDef* bodyDef, b2FixtureDef* fixtureDef)
{
	body = world->CreateBody(bodyDef);
	body->CreateFixture(fixtureDef);

	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		b2Shape::Type shapeType = fixture->GetType();
		if (shapeType == b2Shape::e_polygon)
		{
			b2PolygonShape* polygonShape = (b2PolygonShape*)fixture->GetShape();
			vertices.setPrimitiveType(sf::Quads);

			int verticies = polygonShape->GetVertexCount();
			for (int i = 0; i < verticies; i++)
			{
				vertices.append(sf::Vector2f(polygonShape->GetVertex(i).x * scale, polygonShape->GetVertex(i).y * scale));
			}
		}
		else if (shapeType == b2Shape::e_circle)
		{
			b2CircleShape* circleShape = (b2CircleShape*)fixture->GetShape();
			// TODO: add circle handling
		}
	}
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Get transforms
	b2Vec2 position = body->GetPosition();
	// Apply transforms
	states.transform.rotate(body->GetAngle() * radToDeg);
	states.transform.translate(sf::Vector2f(scale * position.x, scale * -position.y));
	// Draw vertex array
	target.draw(vertices, states);
}
