#pragma once

#include <SFML/Graphics.hpp>

class BackgroundManager
{
public:
	void Load();
	const void Render(sf::RenderTarget& target) const;
	const void Update();

private:
	float m_offset = 0.f;

	sf::Sprite m_background;
	sf::Texture m_backgroundTexture;

	sf::Clock m_clock;
	sf::Shader m_parallaxShader;
};