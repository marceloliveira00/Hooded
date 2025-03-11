#include "MapManager.hpp"

const void MapManager::ConvertSketch(Map* map, sf::Image mapSketch, unsigned mapSketch_X, unsigned mapSketch_Y) const
{
	map->clear();
	map->resize(mapSketch_X);

	for (unsigned short x = 0; x < mapSketch_X; ++x)
	{
		for (unsigned short y = 0; y < mapSketch_Y; ++y)
		{
			sf::Color pixel = mapSketch.getPixel(x, y);

			if (pixel == sf::Color(127, 127, 127)) (*map)[x][y] = Cell::MapBoundary;

			else if (pixel == sf::Color(80, 48, 30)) (*map)[x][y] = Cell::Box;

			else if (pixel == sf::Color(88, 84, 25)) (*map)[x][y] = Cell::SmallBush;

			else if (pixel == sf::Color(89, 85, 26)) (*map)[x][y] = Cell::TallBush;

			else if (pixel == sf::Color(90, 86, 27)) (*map)[x][y] = Cell::BigBush;

			else if (pixel == sf::Color(24, 62, 12)) (*map)[x][y] = Cell::SmallTree;

			else if (pixel == sf::Color(25, 63, 13)) (*map)[x][y] = Cell::TallTree;

			else if (pixel == sf::Color(185, 122, 87)) (*map)[x][y] = Cell::Hill;

			else if (pixel == sf::Color(34, 177, 76)) (*map)[x][y] = Cell::Grass;

			else (*map)[x][y] = Cell::Empty;
		}
	}
}

const void MapManager::DrawMap(const Map* map, const sf::Image& mapSketch, const sf::Texture& mapTexture, const sf::Texture& mapPropsTexture, sf::RenderTarget& target) const
{
	// TODO: only draw the part of the map that is visible on the screen.

	sf::Sprite cellSprite;

	for (unsigned short x = 0; x < mapSketch.getSize().x; ++x)
	{
		for (unsigned short y = 0; y < mapSketch.getSize().y; ++y)
		{
			// ignoring the following pixels.
			if ((*map)[x][y] == Cell::Empty || (*map)[x][y] == Cell::MapBoundary) continue;

			sf::Color pixel = mapSketch.getPixel(x, y);

			unsigned short rectLeft = 0, rectTop = 0, spriteHeight = 0, spriteWidth = 0;

			if (DrawMapProps(map, x, y, rectLeft, rectTop, spriteWidth, spriteHeight))
			{
				cellSprite.setTexture(mapPropsTexture);

				// subtracting the sprite size is necessary since some sprites may not have the default sprite size
				cellSprite.setPosition((float)DEFAULT_SPRITE_SIZE_X_Y * x + DEFAULT_SPRITE_SIZE_X_Y - spriteWidth, (float)DEFAULT_SPRITE_SIZE_X_Y * y + DEFAULT_SPRITE_SIZE_X_Y - spriteHeight);
				cellSprite.setTextureRect(sf::IntRect(rectLeft, rectTop, spriteWidth, spriteHeight));
			}
			else
			{
				unsigned short spriteX = 0, spriteY = 0;

				if ((*map)[x][y] == Cell::Hill)
				{
					if (x > 0 && (*map)[x - 1][y] == Cell::Hill)
						spriteX = 1;
					if ((*map)[x + 1][y] != Cell::Hill)
						spriteX = 2;
				}
				else if ((*map)[x][y] == Cell::Grass)
				{
					if (x > 0 && (*map)[x - 1][y] == Cell::Grass)
						spriteX = 1;
					if ((*map)[x + 1][y] != Cell::Grass)
						spriteX = 2;
					if (y > 0 && (*map)[x][y - 1] == Cell::Grass)
						spriteY = 1;
					if ((*map)[x][y + 1] != Cell::Grass)
						spriteY = 2;
				}
				else continue;

				cellSprite.setTexture(mapTexture);
				cellSprite.setPosition((float)DEFAULT_SPRITE_SIZE_X_Y * x, (float)DEFAULT_SPRITE_SIZE_X_Y * y);
				cellSprite.setTextureRect(sf::IntRect(DEFAULT_SPRITE_SIZE_X_Y * spriteX, DEFAULT_SPRITE_SIZE_X_Y * spriteY, DEFAULT_SPRITE_SIZE_X_Y, DEFAULT_SPRITE_SIZE_X_Y));
			}

			target.draw(cellSprite);
		}
	}
}

const bool MapManager::DrawMapProps(const Map* map, unsigned short x, unsigned short y, unsigned short& pixelX, unsigned short& pixelY, unsigned short& spriteX, unsigned short& spriteY) const
{
	if ((*map)[x][y] == Cell::Box)
	{
		pixelX = 42;
		pixelY = 19;
		spriteX = 45;
		spriteY = 45;

		return true;
	}

	else if ((*map)[x][y] == Cell::SmallBush)
	{
		pixelX = 356;
		pixelY = 579;
		spriteX = 57;
		spriteY = 29;

		return true;
	}
	else if ((*map)[x][y] == Cell::TallBush)
	{
		pixelX = 452;
		pixelY = 573;
		spriteX = 89;
		spriteY = 36;

		return true;
	}
	else if ((*map)[x][y] == Cell::BigBush)
	{
		pixelX = 576;
		pixelY = 572;
		spriteX = 95;
		spriteY = 37;

		return true;
	}

	else if ((*map)[x][y] == Cell::SmallTree)
	{
		pixelX = 576;
		pixelY = 572;
		spriteX = 95;
		spriteY = 37;

		return true;
	}
	else if ((*map)[x][y] == Cell::TallTree)
	{
		pixelX = 831;
		pixelY = 447;
		spriteX = 153;
		spriteY = 162;

		return true;
	}

	return false;
}

const void MapManager::Load(const Level level)
{
	const std::string levelPath = "Assets/Maps/LevelSketch" + std::to_string(level);
	m_mapSketch.loadFromFile(levelPath + ".png"); // set map sketch

	const sf::Vector2u mapSize = m_mapSketch.getSize();
	ConvertSketch(m_map, m_mapSketch, mapSize.x, mapSize.y);

	m_mapTexture.loadFromFile("Assets/Maps/Village/TilesetGround.png");
	m_mapPropsTexture.loadFromFile("Assets/Props/VillageProps.png");
}

const bool MapManager::MapCollision(const float nextPosX, const float nextPosY, const sf::Vector2i nextSize, const EntityStatus status) const
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

const void MapManager::Render(sf::RenderTarget& target) const
{
	DrawMap(m_map, m_mapSketch, m_mapTexture, m_mapPropsTexture, target);
}

const bool MapManager::SpriteOnGround(float posX, float posY, sf::Vector2i size) const
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
