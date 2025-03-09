#include "Managers/GameManager.hpp"

int main()
{
	GameManager game;

	while (game.Running())
	{
		game.Render();
		game.Update();
	}

	return 0;
}