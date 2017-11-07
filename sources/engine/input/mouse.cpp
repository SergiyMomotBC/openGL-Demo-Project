#include "mouse.h"

double Mouse::mScrollWheelYOffset = 0.0;

void Mouse::hideCursor()
{
	glfwSetInputMode(mMainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Mouse::restoreCursor()
{
	glfwSetInputMode(mMainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Mouse::isButtonPressed(int glfwMouseButton) const
{
	return glfwGetMouseButton(mMainWindow, glfwMouseButton) == GLFW_PRESS;
}

bool Mouse::isButtonReleased(int glfwMouseButton) const
{
	return glfwGetMouseButton(mMainWindow, glfwMouseButton) == GLFW_RELEASE;
}

double Mouse::getScrollWheelOffset()
{
	//return current value and set to 0
	double temp = mScrollWheelYOffset;
	mScrollWheelYOffset = 0.0;
	return temp;
}

void Mouse::scroll_callback(GLFWwindow * w, double xoffset, double yoffset)
{
	mScrollWheelYOffset = yoffset;
}

Point2D Mouse::getPointerPosition() const
{
	double xpos, ypos;
	glfwGetCursorPos(mMainWindow, &xpos, &ypos);

	return Point2D(xpos, ypos);
}

