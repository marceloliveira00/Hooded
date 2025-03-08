#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Entity.hpp"
#include "../Headers/MapManager.hpp"

class BlueHooded : public Entity
{
public:
	BlueHooded();

	const void Render(sf::RenderTarget* target) const;
	const void Update(float deltaTime, MapManager& mapManager);

private:
	void InitVariables();
	void InitBlueHooded();
	const void Move();
};

