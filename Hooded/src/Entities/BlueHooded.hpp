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
	const void DefineSpriteCoordinates(SpriteCoordinates& spriteCoordinates) const override;
	const void InitVariables();
	const void InitBlueHooded();
	const void Move();
};

