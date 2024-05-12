#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Camera.hpp"
#include "../Headers/Entity.hpp"
#include "../Headers/MapManager.hpp"
#include "../Headers/Enums/EntityDirection.hpp"
#include "../Headers/Enums/EntityStatus.hpp"

class Hooded : protected Entity
{
public:
	Hooded();

	const void Render(sf::RenderTarget* target) const;
	const void Update(Camera& camera, float deltaTime, MapManager& mapManager);

private:
	sf::Clock m_clock;
	bool m_dematerialized = false;
	EntityDirection m_hoodedDirection = EntityDirection::Right;
	const float m_gravity = 1.f;
	EntityStatus m_hoodedStatus = EntityStatus::Idle;
	const float m_initialHoodedPosX = 250.f;
	const float m_initialHoodedPosY = 150.f;
	float m_jumpPosY = 0.f;
	float m_jumpSpeed = 0.02f;
	unsigned short m_textureIndex = 0;

	sf::Sprite m_hooded;
	sf::RectangleShape m_hoodedBoundingRectangle;
	sf::Texture m_hoodedTexture;

	/// <param name="frames">Number of frames that should wait to update the index</param>
	/// <param name="tiles">Number of tiles in the spritesheet row</param>
	/// <returns>The texture animation index</returns>
	const int GetTextureIndex(unsigned short frames, unsigned short tiles, bool restartAnimation) const;
	void InitVariables();
	void InitHooded();
	const void Dematerialize();
	const void Move(Camera& camera, float deltaTime, MapManager& mapManager);
};

