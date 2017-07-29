#pragma once

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

class Entity : public sf::Drawable
{
public:
	Entity(b2World* world);

	void createBody(b2BodyDef* bodyDef);
	void addFixture(b2FixtureDef* fixtureDef);

	void setTexture(const sf::Texture* tex);
	void setShape(std::vector<sf::Vector2f> verts);
	void setTextureCoords(std::vector<sf::Vector2f> texCoords);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	b2Body* body;
private:
	const sf::Vector2f scale = sf::Vector2f(4, 4);

	b2World* world;

	sf::VertexArray vertices;
	const sf::Texture* texture;
};