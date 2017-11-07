#include "game.h"

#include <chrono>
#include "../sources/scenes/main_scene.h"

using namespace std::chrono;

//static data members
Game Game::sInstance;
bool Game::sWasRequested = false;

//game object can be requested only once
Game* Game::makeInstance()
{
	//check if was previously requested and return either game pointer or null
	if (!sWasRequested) {
		sWasRequested = true;
		return &sInstance;
	} else {
		return nullptr;
	}
}

int Game::initialize()
{
	//initialize GLFW library
	if (!glfwInit())
		return GAME_INIT_FAILURE;

	//create main window
	mWindow = new Window(WIDTH, HEIGHT, "CISC 3620 Assignment #1", false);

	//no fps limit by GLFW system
	glfwSwapInterval(0);

	//initialize GLAD openGL function wrapper
	if (!gladLoadGL())
		return GAME_INIT_FAILURE;

	//initialize input system
	Input::startUp(*mWindow);

	//create scene manager with initial scene
	mSceneManager = new GameSceneManager(new MainScene());

	//openGL setupo
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//success if reached this point
	return GAME_INIT_SUCCESS;
}

void Game::run()
{
	//start game and show the window
	mIsRunning = true;
	mWindow->show();

	//time related variables
	auto prevTime = high_resolution_clock::now();
	decltype(prevTime) currTime;
	double passedTime = 0.0, targetFrameTime = 0.0;

	//main game loop
	while (mIsRunning && !mWindow->willBeClosed()) {
		//calculate time passed since previous frame
		currTime = high_resolution_clock::now();
		passedTime += duration_cast<duration<double>>(currTime - prevTime).count();
		prevTime = currTime;

		targetFrameTime = 1.0 / Game::TARGET_FPS;

		//update if it is right time
		while (passedTime >= targetFrameTime) {
			//allow GLFW system to poll events
			glfwPollEvents();

			//frame logic and rendering
			mSceneManager->runFrame(targetFrameTime);

			//double buffer swapping
			glfwSwapBuffers(mWindow->getGLFWpointer());

			passedTime -= targetFrameTime;
		}
	}

	//window is not needed any more
	mWindow->hide();
}

Game::~Game() {
	delete mWindow;

	//stop GLFW system
	glfwTerminate();
}
