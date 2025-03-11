#pragma once

#include <SFML/Graphics.hpp>

#include "../Camera.hpp"
#include "../Entities/Entity.hpp"
#include "../Managers/MapManager.hpp"

class Hooded : public Entity
{
public:
	Hooded();

	const void Render(sf::RenderTarget* target);
	const void Update(Camera& camera, float deltaTime, MapManager& mapManager, std::vector<Entity*>& entities);

private:
	const void Actions(Camera& camera, const float deltaTime, MapManager& mapManager, std::vector<Entity*>& enemies);
	void Attack(const float deltaTime, std::vector<Entity*>& enemies);
	const void DefineSpriteCoordinates(SpriteCoordinates& spriteCoordinates) const override;
	void InitVariables();
	void InitHooded();
	const void Dematerialize();
	const void ResetJump(const float deltaTime, MapManager& mapManager);
	const void Move(const float deltaTime, MapManager& mapManager);
};

