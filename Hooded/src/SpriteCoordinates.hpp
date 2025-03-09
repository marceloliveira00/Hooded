#pragma once

struct SpriteCoordinates
{
	unsigned short colNumber = 1;
	unsigned short rowIndex = 1;

	SpriteCoordinates();
	/// @param colNumber Number of the row the sprite is in
	/// @param rowNumber Number of the row the sprite is in
	SpriteCoordinates(unsigned short colNumber, unsigned short rowNumber);
};