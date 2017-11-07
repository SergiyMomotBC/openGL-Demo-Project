#ifndef MOUSE_H
#define MOUSE_H

#include "../sources/engine/geometry/point_2d.h"
#include "../sources/engine/windowing/window.h"

class Mouse
{
public:
	/* Creates a mouse object which works with a given window. */
	Mouse(const Window& mainWindow) : mMainWindow(mainWindow.getGLFWpointer()) {
		glfwSetScrollCallback(mMainWindow, scroll_callback);
	}

	/* Checks if specified mouse button is pressed. */
	bool isButtonPressed(int glfwMouseButton) const ;

	/* Checks if specified mouse button is released. */
	bool isButtonReleased(int glfwMouseButton) const;

	/* Returns position of mouse pointer in window's coordinate system. */
	Point2D getPointerPosition() const;

	/* Hides cursor. */
	void hideCursor();

	/* Makes cursor visible. */
	void restoreCursor();

	/* Returns mouse's scroll wheel vertical displacement. */
	double getScrollWheelOffset();

	//no copy allowed
	Mouse(const Mouse& nocopy) = delete;
	Mouse& operator=(const Mouse& nocopy) = delete;

	/* Destructor. */
	virtual ~Mouse() {}

private:
	GLFWwindow* mMainWindow;	//not owner

	static double mScrollWheelYOffset;

	static void scroll_callback(GLFWwindow* w, double xoffset, double yoffset);
};



#endif
