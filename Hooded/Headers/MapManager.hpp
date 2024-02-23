#pragma once

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
	const void Render(sf::RenderTarget* target);
	const void Update();

private:
	const short m_levelHeight = 16;
	const short m_levelWidth = 64;

	float m_offsetX = 0.f;
	float m_offsetY = 0.f;

	const short m_tileHeight = 32;
	const short m_tileWidth = 32;

	unsigned short m_visibleTilesX = SCREEN_WIDTH / m_tileWidth;
	unsigned short m_visibleTilesY = SCREEN_HEIGHT / m_tileHeight;

	sf::Sprite m_cellSprite;
	sf::Image m_mapSketch;
	sf::Texture m_mapTexture;
};

