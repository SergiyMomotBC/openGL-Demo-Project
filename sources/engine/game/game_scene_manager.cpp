#include "game_scene_manager.h"

GameSceneManager::GameSceneManager(IGameScene* initialScene) : mScenes()
{
	mCurrentScene = initialScene;
	mCurrentScene->onStart();
}

void GameSceneManager::changeScene(IGameScene* newScene)
{
	if(mCurrentScene)
		mCurrentScene->onClose();
	
	delete mCurrentScene;

	mCurrentScene = newScene;
	mCurrentScene->onStart();
}

void GameSceneManager::pushScene(IGameScene* newScene)
{
	mCurrentScene->onPause();
	mScenes.push(mCurrentScene);
	mCurrentScene = newScene;
	mCurrentScene->onStart();
}

void GameSceneManager::popScene()
{
	if (mScenes.empty()) return;

	mCurrentScene->onClose();
	delete mCurrentScene;
	mCurrentScene = mScenes.top();
	mScenes.pop();
	mCurrentScene->onResume();
}

void GameSceneManager::runFrame(double deltaTime)
{
	if (mCurrentScene) {
		mCurrentScene->onUpdate(deltaTime);
		mCurrentScene->onRender();
	}
}

GameSceneManager::~GameSceneManager()
{
	if(mCurrentScene)
		mCurrentScene->onClose();

	delete mCurrentScene;
}
