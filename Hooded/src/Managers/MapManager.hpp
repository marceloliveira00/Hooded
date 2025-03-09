#pragma once

#include <algorithm>
#include <bitset>
#include <SFML/Graphics.hpp>
#include <unordered_set>

#include "../Enums/EntityStatus.hpp"
#include "../Enums/Level.hpp"
#include "../GameConfig.hpp"

class MapManager
{
public:
	Map* m_map;

	MapManager();
	~MapManager();

	void Load(Level level);
	bool MapCollision(float nextPosX, float nextPosY, sf::Vector2i nextSize, EntityStatus status);
	const void Render(sf::RenderTarget& target);
	bool SpriteOnGround(float posX, float posY, sf::Vector2i size);

private:
	sf::Sprite m_cellSprite;
	sf::Image m_mapSketch;
	sf::Texture m_mapTexture;
	sf::Texture m_mapPropsTexture;
	std::vector<sf::Vector2i> m_tiles;

	void ConvertSketch(Map* map, sf::Image mapSketch, unsigned mapSize_X, unsigned mapSize_Y);
	void DrawMap(const Map* map, sf::Image& mapSketch, sf::Texture& mapTexture, sf::Texture& m_mapPropsTexture, sf::RenderTarget& target);
	bool DrawMapProps(const Map* map, unsigned short x, unsigned short y, unsigned short& pixelX, unsigned short& pixelY, unsigned short& spriteX, unsigned short& spriteY);

};

// custom hash function for sf::Vector2i
struct Vector2iHash
{
	std::size_t operator()(const sf::Vector2i& v) const noexcept
	{
		return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
	}
};

// custom equality operator (needed for unordered_set)
struct Vector2iEqual
{
	bool operator()(const sf::Vector2i& a, const sf::Vector2i& b) const noexcept
	{
		return a.x == b.x && a.y == b.y;
	}
};