#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Entity.hpp"
#include "../Headers/MapManager.hpp"

class BlueHooded : protected Entity
{
public:
	BlueHooded();

	const void Render(sf::RenderTarget* target) const;
	const void Update(float deltaTime, MapManager& mapManager);

private:
	const float m_initialBlueHoodedPosX = 300.f;
	const float m_initialBlueHoodedPosY = 319.799927f;

	sf::Sprite m_blueHooded;
	sf::RectangleShape m_blueHoodedBoundingRectangle;
	sf::Texture m_blueHoodedTexture;

	void InitVariables();
	void InitBlueHooded();
	const void Move();
};

