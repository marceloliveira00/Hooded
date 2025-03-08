#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Entity.hpp"
#include "../Headers/MapManager.hpp"

class Swordsman : protected Entity
{
public:
	Swordsman();

	const void Render(sf::RenderTarget* target) const;
	const void Update(float deltaTime, MapManager& mapManager);

private:
	void InitVariables();
	void InitSwordsman();
	const void Move();
};

