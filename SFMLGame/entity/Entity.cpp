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

void Entity::setTexture(const sf::Texture* tex)
{
	texture = tex;
	
	// Test texture by updating coords
	// Implement texture and model loader later
	float left = 0.0f;
	float right = left + texture->getSize().x;
	float top = 0.0f;
	float bottom = top + texture->getSize().y;
	vertices[1].texCoords = sf::Vector2f(left, top);
	vertices[0].texCoords = sf::Vector2f(left, bottom);
	vertices[2].texCoords = sf::Vector2f(right, top);
	vertices[3].texCoords = sf::Vector2f(right, bottom);

}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Get transforms
	b2Vec2 position = body->GetPosition();
	// Apply transforms
	states.transform.rotate(body->GetAngle() * radToDeg);
	states.transform.translate(sf::Vector2f(scale * position.x, scale * -position.y));
	// Apply texture if assigned
	if (texture) {
		states.texture = texture;
	}
	// Draw vertex array
	target.draw(vertices, states);
}
