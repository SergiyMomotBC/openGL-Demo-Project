#include "window.h"

Window::Window() {
	createWindow();
}

Window::Window(int width, int height, std::string title, bool resizable ) {
	createWindow(width, height, title, resizable);
}

void Window::createWindow(int width, int height, std::string title, bool resizable, bool visible) {
	//initialization
	mWidth = width;
	mHeight = height;
	mTitle = title;
	mIsResizable = resizable;
	mIsVisible = visible;

	//antialiasing 4x 
	glfwWindowHint(GLFW_SAMPLES, 4);

	//make window resizable depending on constructor argument
	glfwWindowHint(GLFW_RESIZABLE, (resizable) ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, (visible) ? GL_TRUE : GL_FALSE);

	mWindowPtr = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(mWindowPtr);
}
