#ifndef GAME_SCENE_MANAGER_H
#define GAME_SCENE_MANAGER_H

#include <stack>
#include "game_scene.h"

class GameSceneManager final
{
public:
	/* Default constructor with no scene active. */
	GameSceneManager() : mCurrentScene(nullptr), mScenes() {}

	/* Creates a manager with the initial active scene. */
	GameSceneManager(IGameScene* initialScene);

	//no copy allowed
	GameSceneManager(const GameSceneManager& nocopy) = delete;
	GameSceneManager& operator=(const GameSceneManager& nocopy) = delete;

	/* Destroys the current scene and shows a new one. */
	void changeScene(IGameScene* newScene);

	/* Pushes the current scene to stack so it could become active after the new one will be destroyed. */
	void pushScene(IGameScene* newScene);

	/* Makes scene which is on the top of the stack to become active again and destroys the current one. */
	void popScene();

	/* Runs one frame of the game. */
	void runFrame(double deltaTime);

	/* Destructor. */
	virtual ~GameSceneManager();

private:
	IGameScene* mCurrentScene;
	std::stack<IGameScene*> mScenes;
};

#endif
