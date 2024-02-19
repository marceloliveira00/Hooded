#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Hooded : protected Entity
{
public:
	Hooded();

	const void Render(sf::RenderTarget& target) const;
	const void Update(float deltaTime);

private:
	sf::Texture hoodedTexture;
	sf::Sprite hooded;

	void InitVariables();
	void InitHooded();
	const void Move(float deltaTime, sf::Sprite* sprite) const;
};

