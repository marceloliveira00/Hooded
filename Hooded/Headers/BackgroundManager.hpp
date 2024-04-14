#pragma once

#include <SFML/Graphics.hpp>

class BackgroundManager
{
public:
	void Load();
	const void Render(sf::RenderTarget& target) const;

private:
	sf::Sprite m_background;
	sf::Texture m_backgroundTexture;
};