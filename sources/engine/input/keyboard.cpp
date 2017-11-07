#include "keyboard.h"

Keyboard::Keyboard(const Window& mainWindow)
{
	mEventSource = mainWindow.getGLFWpointer();
}

bool Keyboard::isKeyPressed(int key) const
{
	return glfwGetKey(mEventSource, key) == GLFW_PRESS;
}

bool Keyboard::isKeyReleased(int key) const
{
	return glfwGetKey(mEventSource, key) == GLFW_RELEASE;
}

