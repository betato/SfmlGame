#include "Entity.h"

#include <iostream>

static const float radToDeg = 180.0f / 3.141592f;

Entity::Entity(b2World* world)
{
	Entity::world = world;
	vertices.setPrimitiveType(sf::Triangles);
}

void Entity::createBody(b2BodyDef * bodyDef)
{
	body = world->CreateBody(bodyDef);
}

void Entity::addFixture(b2FixtureDef * fixtureDef)
{
	body->CreateFixture(fixtureDef);
}

void Entity::setTexture(const sf::Texture* tex)
{
	texture = tex;
}

void Entity::setShape(sf::VertexArray vertices)
{
	// Copy vertex array
	Entity::vertices.clear();
	int vertexCount = vertices.getVertexCount();
	for (int i = 0; i < vertexCount; i++)
	{
		Entity::vertices.append(vertices[i]);
	}
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Get transforms
	b2Vec2 position = body->GetPosition();
	// Apply transforms
	states.transform.translate(sf::Vector2f(position.x * scale.x, -position.y * scale.y));
	states.transform.rotate(body->GetAngle() * radToDeg);
	states.transform.scale(scale);
	// Apply texture if assigned
	if (texture) {
		states.texture = texture;
	}
	// Draw vertex array
	target.draw(vertices, states);
}
