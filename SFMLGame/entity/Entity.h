#pragma once

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

class Entity : public sf::Drawable
{
public:
	Entity(b2World* world, b2BodyDef* bodyDef, b2FixtureDef* fixtureDef);

	void setTexture(const sf::Texture* tex);
	void Entity::updateTexCoords();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	b2Body* body;
private:

	const float scale = 4.0f;

	sf::VertexArray vertices;
	const sf::Texture* texture;
};