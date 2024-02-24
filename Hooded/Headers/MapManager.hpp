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
	sf::Sprite m_cellSprite;
	sf::Image m_mapSketch;
	sf::Texture m_mapTexture;
};

