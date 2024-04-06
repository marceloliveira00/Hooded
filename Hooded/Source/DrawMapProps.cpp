#include "../Headers/DrawMapProps.h"

bool DrawMapProps(const Map* map, unsigned short x, unsigned short y, unsigned short& pixelX, unsigned short& pixelY, unsigned short& spriteX, unsigned short& spriteY)
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
