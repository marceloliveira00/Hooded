#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "../Managers/MapManager.hpp"

class Swordsman : protected Entity
{
public:
	Swordsman();

	const void Render(sf::RenderTarget* target) const;
	const void Update(const float deltaTime, const MapManager& mapManager);

private:
	const void InitVariables();
	const void InitSwordsman();
	const void Move();
};

