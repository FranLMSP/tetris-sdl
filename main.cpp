#include "Game.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class Game;

int main(int argc, char** args)
{
	Game game;
	game.init();
	game.~Game();

	system("pause");
	return 0;
}
