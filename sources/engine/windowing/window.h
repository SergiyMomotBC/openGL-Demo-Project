#ifndef WINDOW_h
#define WINDOW_h

#include <string>
#include "glfw/glfw3.h"

class Window
{
public:
	/* Default constructor which creates a resizable window of size 640x480. */
	Window();

	/* Creates a window object with a given size, title and resizable flag. */
	Window(int width, int height, std::string title, bool resizable = true);

	/* Window's width getter. */
	int getWidth() const {
		return mWidth;
	}

	/* Window's height getter. */
	int getHeight() const {
		return mHeight;
	}

	/* Window's width setter. */
	void setWidth(int newWidth) {
		mWidth = newWidth;
		glfwSetWindowSize(mWindowPtr, mWidth, mHeight);
	}

	/* Window's height setter. */
	void setHeight(int newHeight) {
		mHeight = newHeight;
		glfwSetWindowSize(mWindowPtr, mWidth, mHeight);
	}

	/* Window's size setter. */
	void setSize(int width, int height) {
		mWidth = width;
		mHeight = height;
		glfwSetWindowSize(mWindowPtr, mWidth, mHeight);
	}

	/* Window's title getter. */
	std::string getTitle() const {
		return mTitle;
	}

	/* Window's title setter. */
	void setTitle(std::string newTitle) {
		mTitle = newTitle;
		glfwSetWindowTitle(mWindowPtr, mTitle.c_str());
	}

	/* Checks if window is resizable. */
	bool isResizable() const {
		return mIsResizable;
	}

	/* Makes window visible. */
	void show() {
		mIsVisible = true;
		glfwShowWindow(mWindowPtr);
	}

	/* Hides the window without destroying it, so it can be easily shown later. */
	void hide() {
		mIsVisible = false;
		glfwHideWindow(mWindowPtr);
	}

	/* Checks if window is about to be closed. */
	bool willBeClosed() {
		return  glfwWindowShouldClose(mWindowPtr) == 1;
	}

	/* Returns a raw GLFW window object pointer for GLFW functions access. */
	GLFWwindow* getGLFWpointer() const {
		return mWindowPtr;
	}

	/* Checks if window is visible. */
	bool isVisible() const {
		return mIsVisible;
	}

	/* Destructor. */
	virtual ~Window() {
		glfwDestroyWindow(mWindowPtr);
	}

private:
	//will be deleted by glfwDestroyWindow function
	GLFWwindow* mWindowPtr;

	int mWidth, mHeight;
	std::string mTitle;
	bool mIsResizable;
	bool mIsVisible;

	void createWindow(int width = 640, 
					  int height = 480, 
					  std::string title = "New window",
					  bool resizable = true, 
					  bool visible = false);
};

#endif
