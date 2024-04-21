#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Camera.hpp"

class BackgroundManager
{
public:
	void Load();
	const void Render(sf::RenderTarget& target) const;
	const void Update(Camera& camera);

private:
	float m_backgroundHalfWidth = 0.f;
	float m_offset = 0.f;

	sf::Sprite m_background;
	sf::Texture m_backgroundTexture;

	sf::Clock m_clock;
	sf::Shader m_parallaxShader;
};