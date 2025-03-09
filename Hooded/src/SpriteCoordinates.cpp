#include "SpriteCoordinates.hpp"

SpriteCoordinates::SpriteCoordinates() { }

SpriteCoordinates::SpriteCoordinates(unsigned short colNumber, unsigned short rowIndex)
{
	this->colNumber = colNumber;
	this->rowIndex = rowIndex;
}
