#pragma once

#include <algorithm>
#include <SFML/Graphics.hpp>

#include "../Headers/ConvertSketch.hpp"
#include "../Headers/DrawMap.hpp"
#include "../Headers/Enums/Level.hpp"
#include "../Headers/GameConfig.hpp"

class MapManager
{
public:
	Map* m_map;

	MapManager();
	~MapManager();

	void Load(Level level);
	bool MapCollision(float nextPosX, float nextPosY, sf::Vector2i nextSize, bool dematerialized = false);
	bool SpriteOnGround(float posX, float posY, sf::Vector2i size);
	const void Render(sf::RenderTarget* target);
	const void Update();

private:
	sf::Sprite m_cellSprite;
	sf::Image m_mapSketch;
	sf::Texture m_mapTexture;
	std::vector<sf::Vector2i> m_tiles;
};

