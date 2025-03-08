#pragma once

#include <algorithm>
#include <bitset>
#include <SFML/Graphics.hpp>
#include <unordered_set>

#include "../Headers/ConvertSketch.hpp"
#include "../Headers/DrawMap.hpp"
#include "../Headers/Enums/EntityStatus.hpp"
#include "../Headers/Enums/Level.hpp"
#include "../Headers/GameConfig.hpp"

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
};

#include <SFML/System/Vector2.hpp>

// Custom hash function for sf::Vector2i
struct Vector2iHash
{
	std::size_t operator()(const sf::Vector2i& v) const noexcept
	{
		return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
	}
};

// Custom equality operator (needed for unordered_set)
struct Vector2iEqual
{
	bool operator()(const sf::Vector2i& a, const sf::Vector2i& b) const noexcept
	{
		return a.x == b.x && a.y == b.y;
	}
};
