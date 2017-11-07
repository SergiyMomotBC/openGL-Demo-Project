#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "glfw/glfw3.h"
#include "../windowing/window.h"

class Keyboard final
{
public:
	/* Creates a keyboard object that is associated with a given window object. */
	Keyboard(const Window& mainWindow);

	/* Checks if keyboard button is pressed. */
	bool isKeyPressed(int glfwKey) const;

	/* Checks if keyboard button is released. */
	bool isKeyReleased(int glfwKey) const;

	//no copy allowed
	Keyboard(const Keyboard& nocopy) = delete;
	Keyboard& operator=(const Keyboard& nocopy) = delete;

	/* Destructor. */
	virtual ~Keyboard() {}

private:
	GLFWwindow* mEventSource;	//not owner
};

#endif
