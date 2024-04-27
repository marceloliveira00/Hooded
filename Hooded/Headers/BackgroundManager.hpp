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

	sf::Clock m_clock;

	sf::Texture m_celestialBodyTexture;
	sf::Sprite m_celestialBody;
	sf::Sprite m_clouds;
	sf::Texture m_cloudsTexture;
	sf::Sprite m_lightedClouds;
	sf::Texture m_lightedCloudsTexture;
	sf::Sprite m_sky;
	sf::Texture m_skyTexture;

	sf::Shader m_parallaxShader;
};