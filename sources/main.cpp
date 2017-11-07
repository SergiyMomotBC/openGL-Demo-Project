#include "engine/game/game.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(int argc, char** argv) 
{
	//shouldn't be deleted as 'game' pointer is not the owner of Game object
	Game* game = Game::makeInstance();

	//check if construction and initialization succeeded 
	if (!game || game->initialize() == GAME_INIT_FAILURE)
		return EXIT_FAILURE;

	//run the actual game
	game->run();

	return EXIT_SUCCESS;
}

