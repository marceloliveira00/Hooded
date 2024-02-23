#include "../Headers/MapManager.hpp"

const void MapManager::Render(sf::RenderTarget* target)
{
	DrawMap(m_map, &m_mapSketch, &m_mapTexture, target, 0);
}

const void MapManager::Update()
{
	// calculate top-left most visible tile
	m_offsetX = 1.f - (float)m_visibleTilesX / 2.f;
	m_offsetY = 2.f - (float)m_visibleTilesY / 2.f;

	// clamp camera to game boundaries
	if (m_offsetX < 0) m_offsetX = 0.f;
	if (m_offsetY < 0) m_offsetY = 0.f;
	if (m_offsetX > m_tileWidth - m_visibleTilesX) m_offsetX = (float)m_levelWidth - m_visibleTilesX;
	if (m_offsetY > m_tileHeight - m_visibleTilesY) m_offsetY = (float)m_levelHeight - m_visibleTilesY;
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