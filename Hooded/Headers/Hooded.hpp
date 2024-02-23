#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Entity.hpp"
#include "../Headers/GameConfig.hpp"

class Hooded : protected Entity
{
public:
	Hooded();

	const void Render(sf::RenderTarget* target) const;
	const void Update(float deltaTime);

private:
	const float initialHoodedPosX = 600.f;
	const float initialHoodedPosY = 888.f;
	unsigned short tileHeight = 32;
	unsigned short tileWidth = 32;

	sf::Sprite m_hooded;
	sf::RectangleShape m_hoodedBoundingRectangle;
	sf::Texture m_hoodedTexture;

	void InitVariables();
	void InitHooded();
	const void Move(float deltaTime, sf::Sprite* sprite);
};

