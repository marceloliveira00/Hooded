#include "../Headers/DrawMap.hpp"

void DrawMap(const Map* map, sf::Image* mapSketch, sf::Texture* mapTexture, sf::RenderTarget& target)
{
	// only draw the part of the map that is visible on the screen.
	//unsigned short mapEnd = SCREEN_WIDTH / DEFAULT_SPRITE_SIZE_X_Y;
	//unsigned short mapStart = DEFAULT_SPRITE_SIZE_X_Y;

	sf::Sprite cellSprite(*mapTexture);

	for (unsigned short x = 0; x < mapSketch->getSize().x; ++x)
	{
		for (unsigned short y = 0; y < mapSketch->getSize().y; ++y)
		{
			// ignoring the empty pixels.
			if ((*map)[x][y] == Cell::Empty) continue;

			unsigned short sprite_X = 0;
			unsigned short sprite_Y = 0;

			sf::Color pixel = mapSketch->getPixel(x, y);
			sf::Color pixelDown = sf::Color(0, 0, 0, 0);
			sf::Color pixelLeft = sf::Color(0, 0, 0, 0);
			sf::Color pixelRight = sf::Color(0, 0, 0, 0);
			sf::Color pixelUp = sf::Color(0, 0, 0, 0);

			if ((*map)[x][y] == Cell::Grass)
			{
				if (x > 0 && (*map)[x - 1][y] == Cell::Grass)
					sprite_X = 1;
				if ((*map)[x + 1][y] != Cell::Grass)
					sprite_X = 2;

				if (y > 0 && (*map)[x][y - 1] == Cell::Grass)
					sprite_Y = 1;
				if ((*map)[x][y + 1] != Cell::Grass)
					sprite_Y = 2;
			}

			cellSprite.setPosition((float)DEFAULT_SPRITE_SIZE_X_Y * x, (float)DEFAULT_SPRITE_SIZE_X_Y * y);
			cellSprite.setTextureRect(sf::IntRect(DEFAULT_SPRITE_SIZE_X_Y * sprite_X, DEFAULT_SPRITE_SIZE_X_Y * sprite_Y, DEFAULT_SPRITE_SIZE_X_Y, DEFAULT_SPRITE_SIZE_X_Y));
			target.draw(cellSprite);
		}
	}
}