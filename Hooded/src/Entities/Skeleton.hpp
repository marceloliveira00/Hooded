#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "../Managers/MapManager.hpp"

class Skeleton : protected Entity
{
public:
	Skeleton();

	const void Render(sf::RenderTarget* target) const;
	const void Update(const float deltaTime, MapManager& mapManager);

private:
	const void InitVariables();
	const void InitSkeleton();
	const void Move();
};

