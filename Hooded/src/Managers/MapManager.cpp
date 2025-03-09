#include "MapManager.hpp"

void MapManager::Load(Level level)
{
	const std::string levelPath = "Assets/Maps/LevelSketch" + std::to_string(level);
	m_mapSketch.loadFromFile(levelPath + ".png"); // set map sketch

	const sf::Vector2u mapSize = m_mapSketch.getSize();
	ConvertSketch(m_map, m_mapSketch, mapSize.x, mapSize.y);

	m_mapTexture.loadFromFile("Assets/Maps/Village/TilesetGround.png");
	m_mapPropsTexture.loadFromFile("Assets/Props/VillageProps.png");
}

bool MapManager::MapCollision(float nextPosX, float nextPosY, sf::Vector2i nextSize, EntityStatus status)
{
	if (status == EntityStatus::Dematerialized) return false;

	// compute the bouding box in tile coordinates
	const int left = static_cast<int>(nextPosX) / DEFAULT_SPRITE_SIZE_X_Y;
	const int right = static_cast<int>(nextPosX + nextSize.x) / DEFAULT_SPRITE_SIZE_X_Y;
	const int top = static_cast<int>(nextPosY) / DEFAULT_SPRITE_SIZE_X_Y;
	const int bottom = static_cast<int>(nextPosY + nextSize.y) / DEFAULT_SPRITE_SIZE_X_Y;

	std::unordered_set<sf::Vector2i, Vector2iHash> m_tiles =
	{
		{left, top}, {right, top}, {left, bottom}, {right, bottom},
	};

	// static bitset to quickly check which Cell types are collidable
	// the bitset items set to true, indicating that these cell types are considered collidable
	static const std::bitset<32> collidableBitset = []
	{
		std::bitset<32> b;
		b.set(static_cast<size_t>(Cell::Grass));
		b.set(static_cast<size_t>(Cell::Hill));
		b.set(static_cast<size_t>(Cell::MapBoundary));
		return b;
	}();

	// check if any of the tiles are collidable
	for (const auto& tile : m_tiles)
	{
		if (collidableBitset.test(static_cast<size_t>((*m_map)[tile.x][tile.y]))) return true;
	}

	return false;
}

const void MapManager::Render(sf::RenderTarget& target)
{
	DrawMap(m_map, m_mapSketch, m_mapTexture, m_mapPropsTexture, target);
}

bool MapManager::SpriteOnGround(float posX, float posY, sf::Vector2i size)
{
	// calculate bottom coordinate (avoiding rounding issues)
	const int bottom = static_cast<int>(std::floor(posY + size.y));
	const int left = static_cast<int>(posX);
	const int right = static_cast<int>(posX + size.x);

	// convert to tile indices
	sf::Vector2i bottomLeft(left / DEFAULT_SPRITE_SIZE_X_Y, bottom / DEFAULT_SPRITE_SIZE_X_Y);
	sf::Vector2i bottomRight(right / DEFAULT_SPRITE_SIZE_X_Y, bottom / DEFAULT_SPRITE_SIZE_X_Y);

	// use unordered_set to prevent duplicates
	std::unordered_set<sf::Vector2i, Vector2iHash> groundTiles = { bottomLeft, bottomRight };

	// define ground tiles set
	static const std::unordered_set<Cell> groundCells = { Cell::Grass, Cell::Hill };

	// check if the player is touching the ground
	for (const auto& tile : groundTiles)
	{
		Cell cell = (*m_map)[tile.x][tile.y];
		if (groundCells.find(cell) != groundCells.end()) return true;
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
