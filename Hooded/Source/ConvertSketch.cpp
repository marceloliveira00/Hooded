#include "../Headers/ConvertSketch.hpp"

void ConvertSketch(Map* map, sf::Image mapSketch, unsigned mapSketch_X, unsigned mapSketch_Y)
{
	map->clear();
	map->resize(mapSketch_X);

	// height divided by 3 because the sketch stores the level as 3 layers: blocks, entities, and background tiles.
	const short mapHeight = mapSketch_Y / 3;
	for (unsigned short x = 0; x < mapSketch_X; ++x)
	{
		for (unsigned short y = 0; y < 2 * mapHeight; ++y)
		{
			if (y > mapHeight) continue;

			sf::Color pixel = mapSketch.getPixel(x, y);

			if (pixel == sf::Color(127, 127, 127)) (*map)[x][y] = Cell::MapBoundary;

			if (pixel == sf::Color(0, 0, 0)) (*map)[x][y] = Cell::Grass;

			else(*map)[x][y] = Cell::Empty;
		}
	}
}
