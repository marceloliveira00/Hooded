#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Camera.hpp"
#include "../Headers/Entity.hpp"
#include "../Headers/GameConfig.hpp"
#include "../Headers/MapManager.hpp"

class Hooded : protected Entity
{
public:
	Hooded();

	const void Render(sf::RenderTarget* target) const;
	const void Update(Camera& camera, float deltaTime, MapManager& mapManager);

private:
	bool m_dematerialized = false;
	const float m_initialHoodedPosX = 500.f;
	const float m_initialHoodedPosY = 300.f;
	const unsigned short m_jumpSpeed = 1.1;
	unsigned short m_tileHeight = DEFAULT_SPRITE_SIZE;
	unsigned short m_tileWidth = DEFAULT_SPRITE_SIZE;

	sf::Sprite m_hooded;
	sf::RectangleShape m_hoodedBoundingRectangle;
	sf::Texture m_hoodedTexture;

	void InitVariables();
	void InitHooded();
	const void Move(Camera& camera, float deltaTime, MapManager& mapManager, sf::Sprite& sprite);
};

