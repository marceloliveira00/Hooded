#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Entity.hpp"
#include "../Headers/MapManager.hpp"

class Swordsman : protected Entity
{
public:
	Swordsman();

	const void Render(sf::RenderTarget* target) const;
	const void Update(float deltaTime, MapManager& mapManager);

private:
	const float m_initialSwordsmanPosX = 300.f;
	const float m_initialSwordsmanPosY = 313.5f;

	sf::Sprite m_swordsman;
	sf::RectangleShape m_swordsmanBoundingRectangle;
	sf::Texture m_swordsmanTexture;

	void InitVariables();
	void InitSwordsman();
	const void Move();
};

