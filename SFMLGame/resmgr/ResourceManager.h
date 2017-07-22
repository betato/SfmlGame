#pragma once

#include "TextureManager.h"
#include "SoundManager.h"
#include "FontManager.h"

struct ResourceManager
{
public:
	const sf::Texture& getTexture(TextureName name) const;
	const sf::SoundBuffer& getSound(SoundName name) const;
	const sf::Font& getFont(FontName name) const;

private:
	TextureManager textures;
	SoundManager sounds;
	FontManager fonts;
};