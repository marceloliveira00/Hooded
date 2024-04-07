#pragma once

// TODO: Should we make Props an even/odd number so we don't have to create pass through every pixel in the DrawMapProps again?

enum Cell : unsigned short
{
	Box,
	Empty,
	Grass,
	Hill,
	MapBoundary,
	Wall,

	SmallBush,
	TallBush,
	BigBush,

	SmallTree,
	TallTree
};
