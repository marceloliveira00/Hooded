#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Camera.hpp"
#include "Entity.hpp"
#include "Enums/EntityDirection.hpp"
#include "Enums/EntityStatus.hpp"
#include "MapManager.hpp"

class Hooded : protected Entity
{
public:
	Hooded();
	~Hooded();

	const void Render(sf::RenderTarget* target) const;
	const void Update(Camera& camera, float deltaTime, MapManager& mapManager);

private:
	Animation* m_animation;

	EntityDirection m_hoodedDirection = EntityDirection::Right;
	EntityStatus m_hoodedStatus = EntityStatus::Idle;
	
	const float m_gravity = 1.f;
	const float m_initialHoodedPosX = 250.f;
	const float m_initialHoodedPosY = 150.f;
	float m_jumpPosY = 0.f;
	float m_jumpSpeed = 0.02f;

	sf::Clock m_clock;
	sf::Sprite m_hooded;
	sf::RectangleShape m_hoodedBoundingRectangle;
	sf::Texture m_hoodedTexture;

	const void Actions(Camera& camera, float deltaTime, MapManager& mapManager);
	const void Attack();
	void InitVariables();
	void InitHooded();
	const void Dematerialize();
	const void ResetJump(float deltaTime, MapManager& mapManager);
	const void Move(float deltaTime, MapManager& mapManager);
};

