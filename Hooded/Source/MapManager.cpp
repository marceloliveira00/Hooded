#include "../Headers/MapManager.hpp"

const void MapManager::Render(sf::RenderTarget* target)
{
	DrawMap(m_map, &m_mapSketch, &m_mapTexture, target, 0);
}

const void MapManager::Update()
{
	
}

MapManager::MapManager()
{
	m_map = new Map();
}

MapManager::~MapManager()
{
	delete m_map;
}

void MapManager::Load(Level level)
{
	const std::string levelPath = "Assets/Maps/LevelSketch" + std::to_string(level);
	m_mapSketch.loadFromFile(levelPath + ".png"); // set map sketch

	const sf::Vector2u mapSize = m_mapSketch.getSize();
	ConvertSketch(m_map, m_mapSketch, mapSize.x, mapSize.y);

	m_mapTexture.loadFromFile("Assets/Maps/Village/TilesetGround.png");
}