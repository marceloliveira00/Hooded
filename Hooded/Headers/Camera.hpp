#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/GameConfig.hpp"

class Camera
{
public:
	Camera(float zoomLevel = 300.f);

	const sf::View GetCameraView() const;
	const void SetPosition(const float posX, const float posY);

private:
	sf::Vector2f m_position;

	const float m_camOffsetX = 275.f;
	const float m_camOffsetY = 295.f;
	const float m_viewY = 25.f;
	const float m_zoomLevel;
};

