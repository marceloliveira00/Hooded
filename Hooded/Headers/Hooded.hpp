#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Entity.hpp"
#include "MapManager.hpp"

class Hooded : public Entity
{
public:
	Hooded();
	~Hooded();

	const void Render(sf::RenderTarget* target);
	const void Update(Camera& camera, float deltaTime, MapManager& mapManager, std::vector<Entity*>& entities);

private:
	sf::Clock m_clock;

	const void Actions(Camera& camera, const float deltaTime, MapManager& mapManager, std::vector<Entity*>& enemies);
	void Attack(const float deltaTime, std::vector<Entity*>& enemies);
	void InitVariables();
	void InitHooded();
	const void Dematerialize();
	const void ResetJump(const float deltaTime, MapManager& mapManager);
	const void Move(const float deltaTime, MapManager& mapManager);
};

