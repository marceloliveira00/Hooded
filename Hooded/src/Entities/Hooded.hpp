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
	const void Update(Camera& camera, const float deltaTime, const MapManager& mapManager, const std::vector<Entity*>& entities);

private:
	const void Actions(Camera& camera, const float deltaTime, const MapManager& mapManager, const std::vector<Entity*>& enemies);
	const void Attack(const float deltaTime, const std::vector<Entity*>& enemies);
	const void DefineSpriteCoordinates(SpriteCoordinates& spriteCoordinates) const override;
	const void InitVariables();
	const void InitHooded();
	const void Dematerialize() const;
	const void ResetJump(const float deltaTime, const MapManager& mapManager);
	const void Move(const float deltaTime, const MapManager& mapManager);
};

