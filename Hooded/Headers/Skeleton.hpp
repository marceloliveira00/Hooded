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
	const float m_initialSkeletonPosX = 300.f;
	const float m_initialSkeletonPosY = 319.799927f;

	sf::Sprite m_skeleton;
	sf::RectangleShape m_skeletonBoundingRectangle;
	sf::Texture m_skeletonTexture;

	void InitVariables();
	void InitSkeleton();
	const void Move();
};

