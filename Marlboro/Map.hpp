#pragma once

#include <SFML/Graphics.hpp>

class Map
{
public:
	Map();

	const void Render(sf::RenderTarget& target) const;
	const void Update();

private:

};

