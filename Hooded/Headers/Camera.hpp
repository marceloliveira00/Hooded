#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/GameConfig.hpp"

class Camera
{
public:
	Camera(float zoomLevel = 1000.f);

	const sf::View GetCameraView() const;
	const void SetPosition(const float posX, const float posY);

private:
	sf::Vector2f m_position;
	float m_zoomLevel;
};

