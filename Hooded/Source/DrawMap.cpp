#include "../Headers/DrawMap.hpp"

void DrawMap(const Map* map, sf::Image* mapSketch, sf::Texture* mapTexture, sf::RenderTarget* target, unsigned short view_X)
{
	// only draw the part of the map that is visible on the screen.
	unsigned short mapEnd = (unsigned short)ceil(view_X + SCREEN_WIDTH / DEFAULT_SPRITE_SIZE);
	unsigned short mapHeight = (unsigned short)floor(mapSketch->getSize().y / 3.f);
	unsigned short mapStart = (unsigned short)floor(view_X / DEFAULT_SPRITE_SIZE);

	sf::Sprite cellSprite(*mapTexture);

	for (unsigned short x = mapStart; x < mapEnd; x++)
	{
		for (unsigned short y = 0; y < mapHeight; y++)
		{
			// ignoring the empty pixels.
			if ((*map)[x][y] == Cell::Empty) continue;

			unsigned short sprite_X = 0;
			unsigned short sprite_Y = 0;

			sf::Color pixel = mapSketch->getPixel(x, y + 2 * mapHeight);
			sf::Color pixelDown = sf::Color(0, 0, 0, 0);
			sf::Color pixelLeft = sf::Color(0, 0, 0, 0);
			sf::Color pixelRight = sf::Color(0, 0, 0, 0);
			sf::Color pixelUp = sf::Color(0, 0, 0, 0);

			if ((*map)[x][y] == Cell::Grass)
			{
				if (x > 0 && (*map)[x - 1][y] == Cell::Grass)
					sprite_X = 1;
				if (y > 0 && (*map)[x][y - 1] == Cell::Grass)
					sprite_Y = 1;
				if ((*map)[x][y + 1] != Cell::Grass)
					sprite_Y = 2;
			}

			cellSprite.setPosition((float)DEFAULT_SPRITE_SIZE * x, (float)DEFAULT_SPRITE_SIZE * y);
			cellSprite.setTextureRect(sf::IntRect(DEFAULT_SPRITE_SIZE * sprite_X, DEFAULT_SPRITE_SIZE * sprite_Y, DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE));
			target->draw(cellSprite);
		}
	}
}