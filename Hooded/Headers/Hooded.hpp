#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Camera.hpp"
#include "../Headers/Entity.hpp"
#include "../Headers/GameConfig.hpp"

class Hooded : protected Entity
{
public:
	Hooded();

	const void Render(sf::RenderTarget* target) const;
	const void Update(Camera* camera, float deltaTime);

private:
	const float initialHoodedPosX = 500.f;
	const float initialHoodedPosY = 300.f;
	unsigned short tileHeight = DEFAULT_SPRITE_SIZE;
	unsigned short tileWidth = DEFAULT_SPRITE_SIZE;

	sf::Sprite m_hooded;
	sf::RectangleShape m_hoodedBoundingRectangle;
	sf::Texture m_hoodedTexture;

	void InitVariables();
	void InitHooded();
	const void Move(Camera* camera, float deltaTime, sf::Sprite* sprite);
};

