#pragma once

#include <SFML/Graphics.hpp>

#include "../Entities/Entity.hpp"
#include "../Managers/MapManager.hpp"

class BlueHooded : public Entity
{
public:
	BlueHooded();
	~BlueHooded();

	const void Render(sf::RenderTarget* target) const;
	const void Update(float deltaTime, MapManager& mapManager);

private:
	const void DefineSpriteCoordinates(SpriteCoordinates& spriteCoordinates) const override;
	void InitVariables();
	void InitBlueHooded();
	const void Move();
};

