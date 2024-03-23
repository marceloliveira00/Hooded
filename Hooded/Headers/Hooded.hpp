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
	const float m_gravity = 1.f;
	const float m_initialHoodedPosX = 300.f;
	const float m_initialHoodedPosY = 1080.f;
	float m_jumpPosY = 0.f;
	float m_jumpSpeed = 0.02f;
	bool m_onGround = false;
	unsigned short m_tileHeight = DEFAULT_SPRITE_SIZE_X_Y;
	unsigned short m_tileWidth = DEFAULT_SPRITE_SIZE_X_Y;

	sf::Sprite m_hooded;
	sf::RectangleShape m_hoodedBoundingRectangle;
	sf::Texture m_hoodedTexture;

	/// <param name="frames">Number of frames that should wait to update the index</param>
	/// <param name="tiles">Number of tiles in the spritesheet row</param>
	/// <returns>The texture animation index</returns>
	const int GetTextureIndex(unsigned short frames, short tiles) const;
	void InitVariables();
	void InitHooded();
	const void Dematerialize();
	const void Move(Camera& camera, float deltaTime, MapManager& mapManager);
};

