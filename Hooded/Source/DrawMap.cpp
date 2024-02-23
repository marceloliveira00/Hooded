#include "../Headers/DrawMap.hpp"

void DrawMap(const Map* map, sf::Image* mapSketch, sf::Texture* mapTexture, sf::RenderTarget* target, unsigned short view_X)
{
	// only draw the part of the map that is visible on the screen.
	unsigned short mapEnd = (unsigned short)ceil(view_X + SCREEN_WIDTH / SPRITE_CELL_SIZE);
	unsigned short mapHeight = (unsigned short)floor(mapSketch->getSize().y / 3.f);
	unsigned short mapStart = (unsigned short)floor(view_X / SPRITE_CELL_SIZE);

	sf::Sprite cellSprite(*mapTexture);

	for (unsigned short x = mapStart; x < mapEnd; x++)
	{
		for (unsigned short y = 0; y < mapHeight; y++)
		{
			unsigned short sprite_X = 0;
			unsigned short sprite_Y = 0;

			sf::Color pixel = mapSketch->getPixel(x, y + 2 * mapHeight);
			sf::Color pixelDown = sf::Color(0, 0, 0, 0);
			sf::Color pixelLeft = sf::Color(0, 0, 0, 0);
			sf::Color pixelRight = sf::Color(0, 0, 0, 0);
			sf::Color pixelUp = sf::Color(0, 0, 0, 0);

			cellSprite.setPosition((float)SPRITE_CELL_SIZE * x, (float)SPRITE_CELL_SIZE * y);

			// ignoring the empty pixels.
			if (255 == pixel.a)
			{
				// getting pixels around the pixel we're currently checking.
				if (0 < x) pixelLeft = mapSketch->getPixel(x - 1, y + 2 * mapHeight);

				if (0 < y) pixelUp = mapSketch->getPixel(x, y + 2 * mapHeight - 1);

				if (x < mapSketch->getSize().x - 1) pixelRight = mapSketch->getPixel(1 + x, y + 2 * mapHeight);

				if (y < mapHeight - 1) pixelDown = mapSketch->getPixel(x, 1 + y + 2 * mapHeight);

				if (sf::Color(255, 255, 255) == pixel) // clouds
				{
					sprite_X = 8;

					if (sf::Color(255, 255, 255) == pixelUp) sprite_Y = 1;

					if (sf::Color(255, 255, 255) == pixelLeft)
					{
						if (sf::Color(255, 255, 255) != pixelRight) sprite_X = 9;
					}
					else if (sf::Color(255, 255, 255) == pixelRight) sprite_X = 7;
				}
				else if (sf::Color(146, 219, 0) == pixel) // grass
				{
					sprite_X = 5;

					if (sf::Color(146, 219, 0) == pixelLeft)
					{
						if (sf::Color(146, 219, 0) != pixelRight) sprite_X = 6;
					}
					else if (sf::Color(146, 219, 0) == pixelRight)
					{
						sprite_X = 4;
					}
				}
				else if (sf::Color(0, 73, 0) == pixel) // hills outline
				{
					sprite_Y = 1;

					if (sf::Color(0, 109, 0) == pixelLeft)
					{
						if (sf::Color(0, 109, 0) != pixelRight) sprite_X = 2;
					}
					else if (sf::Color(0, 109, 0) == pixelRight) sprite_X = 1;
				}
				else if (sf::Color(0, 109, 0) == pixel) // hills
				{
					sprite_X = 4;
					sprite_Y = 1;

					if (sf::Color(0, 73, 0) == pixelLeft) sprite_X = 3;
					else if (sf::Color(0, 73, 0) == pixelRight)sprite_X = 5;
				}
				else if (sf::Color(109, 255, 85) == pixel) // flagpole
				{
					sprite_X = 12;

					if (sf::Color(109, 255, 85) == pixelUp) sprite_Y = 1;
				}

				cellSprite.setTextureRect(sf::IntRect(SPRITE_CELL_SIZE * sprite_X, SPRITE_CELL_SIZE * sprite_Y, SPRITE_CELL_SIZE, SPRITE_CELL_SIZE));

				target->draw(cellSprite);
			}

			// drawing the blocks separately from the background tiles.
			if (Cell::Empty != (*map)[x][y])
			{
				if (Cell::Pipe == (*map)[x][y]) // pipes
				{
					if (Cell::Pipe == (*map)[x][y - 1]) sprite_Y = 1;
					else sprite_Y = 0;

					if (Cell::Pipe == (*map)[x - 1][y]) sprite_X = 11;
					else sprite_X = 10;
				}
				else if (Cell::QuestionBlock == (*map)[x][y]) // question blocks
				{
					sprite_X = 1;
					sprite_Y = 0;
				}
				else if (Cell::Wall == (*map)[x][y])
				{
					sprite_Y = 0;

					if (sf::Color(0, 0, 0) == mapSketch->getPixel(x, y)) sprite_X = 2; // walls
					else sprite_X = 3; // solid blocks
				}

				cellSprite.setTextureRect(sf::IntRect(SPRITE_CELL_SIZE * sprite_X, SPRITE_CELL_SIZE * sprite_Y, SPRITE_CELL_SIZE, SPRITE_CELL_SIZE));
				target->draw(cellSprite);
			}
		}
	}
}