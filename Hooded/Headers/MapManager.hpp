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
	const void Render(sf::RenderTarget& target);
	bool SpriteOnGround(float posX, float posY, sf::Vector2i size);

private:
	sf::Sprite m_cellSprite;
	sf::Image m_mapSketch;
	sf::Texture m_mapTexture;
	sf::Texture m_mapPropsTexture;
	std::vector<sf::Vector2i> m_tiles;
};

