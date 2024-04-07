#include "../Headers/DrawMap.hpp"

static bool DrawMapProps(const Map* map, unsigned short x, unsigned short y, unsigned short& pixelX, unsigned short& pixelY, unsigned short& spriteX, unsigned short& spriteY)
{
	if ((*map)[x][y] == Cell::Box)
	{
		pixelX = 42;
		pixelY = 19;
		spriteX = 45;
		spriteY = 45;

		return true;
	}

	return false;
}

void DrawMap(const Map* map, sf::Image& mapSketch, sf::Texture& mapTexture, sf::Texture& mapPropsTexture, sf::RenderTarget& target)
{
	// only draw the part of the map that is visible on the screen.
	//unsigned short mapEnd = SCREEN_WIDTH / DEFAULT_SPRITE_SIZE_X_Y;
	//unsigned short mapStart = DEFAULT_SPRITE_SIZE_X_Y;

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