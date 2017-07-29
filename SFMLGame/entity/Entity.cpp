#include "Entity.h"

static const float radToDeg = 180.0f / 3.141592f;

Entity::Entity(b2World* world, b2BodyDef* bodyDef, b2FixtureDef* fixtureDef)
{
	body = world->CreateBody(bodyDef);
	body->CreateFixture(fixtureDef);
	vertices.setPrimitiveType(sf::Triangles);
}

void Entity::setTexture(const sf::Texture* tex)
{
	texture = tex;
}

void Entity::setShape(std::vector<sf::Vector2f> verts)
{
	vertices.clear();
	std::vector<sf::Vector2f>::iterator it;
	for (it = verts.begin(); it < verts.end(); it++)
	{
		vertices.append(*it);
	}
}

void Entity::setTextureCoords(std::vector<sf::Vector2f> texCoords)
{
	int i = 0;
	std::vector<sf::Vector2f>::iterator it;
	for (it = texCoords.begin(); it < texCoords.end(); it++)
	{
		vertices[i].texCoords = sf::Vector2f(it->x * texture->getSize().x, it->y * texture->getSize().y);
		i++;
 	}
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Get transforms
	b2Vec2 position = body->GetPosition();
	// Apply transforms
	states.transform.rotate(body->GetAngle() * radToDeg);
	states.transform.translate(sf::Vector2f(position.x, -position.y));
	// Apply texture if assigned
	if (texture) {
		states.texture = texture;
	}
	// Draw vertex array
	target.draw(vertices, states);
}
