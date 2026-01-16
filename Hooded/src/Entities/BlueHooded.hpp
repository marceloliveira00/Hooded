#pragma once

#include <SFML/Graphics.hpp>

#include "../Entities/Entity.hpp"
#include "../Managers/MapManager.hpp"

class BlueHooded : public Entity
{
public:
	BlueHooded();

	const void Render(sf::RenderTarget* target) const;
	const void Update(const float deltaTime, const MapManager& mapManager);

private:
	const void Actions(const float deltaTime, const MapManager& mapManager);
	const void DefineSpriteCoordinates(SpriteCoordinates& spriteCoordinates) const override;
	const void InitBlueHooded();
	const void InitVariables();
	const void Jump(const float deltaTime, const MapManager& mapManager);
	const void Move(const float deltaTime, const MapManager& mapManager);
};

