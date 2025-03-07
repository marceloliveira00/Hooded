#pragma once

#include <SFML/Graphics.hpp>

#include "../Headers/Entity.hpp"
#include "../Headers/MapManager.hpp"

class Skeleton : protected Entity
{
public:
	Skeleton();

	const void Render(sf::RenderTarget* target) const;
	const void Update(float deltaTime, MapManager& mapManager);

private:
	void InitVariables();
	void InitSkeleton();
	const void Move();
};

