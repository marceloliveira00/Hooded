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
			if (sf::Color(182, 73, 0) == pixel)
			{
				(*map)[x][y] = Cell::Brick;
			}
			else if (sf::Color(255, 255, 0) == pixel)
			{
				(*map)[x][y] = Cell::Coin;
			}
			// multiple colors because it is needed to know which part of the pipe to draw.
			else if (sf::Color(0, 146, 0) == pixel || sf::Color(0, 182, 0) == pixel || sf::Color(0, 219, 0) == pixel)
			{
				(*map)[x][y] = Cell::Pipe;
			}
			else if (sf::Color(255, 73, 85) == pixel || sf::Color(255, 146, 85) == pixel)
			{
				(*map)[x][y] = Cell::QuestionBlock;
			}
			else if (sf::Color(0, 0, 0) == pixel || sf::Color(146, 73, 0) == pixel)
			{
				(*map)[x][y] = Cell::Wall;
			}
			else
			{
				(*map)[x][y] = Cell::Empty;

				if (sf::Color(0, 255, 255) == pixel)
				{
					//levelFinish = x;
				}
			}
		}
	}
}
