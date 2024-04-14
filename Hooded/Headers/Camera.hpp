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

	const float m_camOffSetX = 275.f;
	const float m_camOffSetY = 256.f;
	const float m_zoomLevel;
};

