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
