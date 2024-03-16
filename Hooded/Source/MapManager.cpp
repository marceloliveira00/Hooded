#include "../Headers/MapManager.hpp"

const void MapManager::Render(sf::RenderTarget* target)
{
	DrawMap(m_map, &m_mapSketch, &m_mapTexture, target, 0);
}

const void MapManager::Update()
{

}

bool MapManager::SpriteOnGround(float posX, float posY, sf::Vector2i size)
{
	const int bottom = (int)posY + size.y;
	const int left = (int)posX;
	const int right = (int)posX + size.x;

	sf::Vector2i bottomLeft(sf::Vector2i(left / DEFAULT_SPRITE_SIZE_X_Y, bottom / DEFAULT_SPRITE_SIZE_X_Y));
	sf::Vector2i bottomRight(sf::Vector2i(right / DEFAULT_SPRITE_SIZE_X_Y, bottom / DEFAULT_SPRITE_SIZE_X_Y));

	m_tiles.clear();

	if (std::find(m_tiles.begin(), m_tiles.end(), bottomLeft) == m_tiles.end()) m_tiles.push_back(bottomLeft);
	if (std::find(m_tiles.begin(), m_tiles.end(), bottomRight) == m_tiles.end()) m_tiles.push_back(bottomRight);

	for (unsigned short i = 0; i < m_tiles.size(); i++)
	{
		// Checks if the player is touching the ground
		if ((*m_map)[bottomLeft.x][bottomLeft.y] == Cell::Grass ||
			(*m_map)[bottomRight.x][bottomRight.y] == Cell::Grass)
		{
			return true;
		}
	}

	return false;
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

bool MapManager::MapCollision(float nextPosX, float nextPosY, sf::Vector2i nextSize, bool dematerialized)
{
	if (dematerialized) return false;

	const int bottom = (int)nextPosY + nextSize.y;
	const int left = (int)nextPosX;
	const int right = (int)nextPosX + nextSize.x;
	const int top = (int)nextPosY;

	sf::Vector2i topLeft(sf::Vector2i(left / DEFAULT_SPRITE_SIZE_X_Y, top / DEFAULT_SPRITE_SIZE_X_Y));
	sf::Vector2i topRight(sf::Vector2i(right / DEFAULT_SPRITE_SIZE_X_Y, top / DEFAULT_SPRITE_SIZE_X_Y));
	sf::Vector2i bottomLeft(sf::Vector2i(left / DEFAULT_SPRITE_SIZE_X_Y, bottom / DEFAULT_SPRITE_SIZE_X_Y));
	sf::Vector2i bottomRight(sf::Vector2i(right / DEFAULT_SPRITE_SIZE_X_Y, bottom / DEFAULT_SPRITE_SIZE_X_Y));

	m_tiles.clear();

	m_tiles.push_back(topLeft);
	if (std::find(m_tiles.begin(), m_tiles.end(), topRight) == m_tiles.end()) m_tiles.push_back(topRight);
	if (std::find(m_tiles.begin(), m_tiles.end(), bottomLeft) == m_tiles.end()) m_tiles.push_back(bottomLeft);
	if (std::find(m_tiles.begin(), m_tiles.end(), bottomRight) == m_tiles.end()) m_tiles.push_back(bottomRight);

	for (unsigned short i = 0; i < m_tiles.size(); i++)
	{
		if ((*m_map)[m_tiles[i].x][m_tiles[i].y] == Cell::Empty) continue;

		if ((*m_map)[m_tiles[i].x][m_tiles[i].y] == Cell::MapBoundary) return true;

		if ((*m_map)[m_tiles[i].x][m_tiles[i].y] == Cell::Grass) return true;
	}

	return false;
}
