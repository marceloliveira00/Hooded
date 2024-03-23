#include "../Headers/ConvertSketch.hpp"

void ConvertSketch(Map* map, sf::Image mapSketch, unsigned mapSketch_X, unsigned mapSketch_Y)
{
	map->clear();
	map->resize(mapSketch_X);

	for (unsigned short x = 0; x < mapSketch_X; ++x)
	{
		for (unsigned short y = 0; y < mapSketch_Y; ++y)
		{
			sf::Color pixel = mapSketch.getPixel(x, y);

			if (pixel == sf::Color(127, 127, 127)) (*map)[x][y] = Cell::MapBoundary;

			if (pixel == sf::Color(0, 0, 0)) (*map)[x][y] = Cell::Grass;

			else(*map)[x][y] = Cell::Empty;
		}
	}
}
