#ifndef GAME_H
#define GAME_H

#include "glad/glad.h"
#include "game_scene_manager.h"
#include "../windowing/window.h"

#define GAME_INIT_SUCCESS 0
#define GAME_INIT_FAILURE 1

class Game final
{
public:
	//game related constants
	static const int TARGET_FPS = 60;
	static const int WIDTH = 1280;
	static const int HEIGHT = 720;

	//singleton style getter but can be called only once
	static Game* makeInstance();

	//all game engine initialization
	int initialize();

	//actual game logic
	void run();

	//will call private deinitialize() method
	~Game();

	//no copy allowed
	Game(const Game& nocopy) = delete;
	Game& operator=(const Game& nocopy) = delete;

private: 
	//no creation through construction
	Game() {}

	//instance of game 
	static Game sInstance;
	static bool sWasRequested;

	bool mIsRunning;
	Window* mWindow;
	GameSceneManager* mSceneManager;
};

#endif