#include "camera.h"

#include <cmath>

Camera::Camera(int width, int height, GLfloat fov, glm::vec3 position)
{
	mWidth = width;
	mHeight = height;

	mPosition = position;
	mDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	mUpAxis = glm::vec3(0.0f, 1.0f, 0.0f);

	mKeyboard = Input::getKeyboard();
	mMouse = Input::getMouse();

	mLastPointerPosition = mMouse->getPointerPosition();

	mYaw = -90.0f;
	mPitch = 0.0f;

	mSpeed = 0.1f;
	mSensitivity = 0.08f;

	mFOV = fov;
}

void Camera::update(double dt)
{
	updatePosition();
	updateDirection();
	updateZoom();
}

void Camera::setPosition(glm::vec3 newPosition)
{
	mPosition = newPosition;
}

void Camera::setDirection(glm::vec3 newDirection)
{
	mDirection = newDirection;
}

void Camera::lookAtPoint(glm::vec3 point)
{
	//set new direction by calculating displacement vector
	mDirection = glm::normalize(point - mPosition);
	
	//recalculate pitch and yaw
	mPitch = glm::degrees(asin(mDirection.y));
	mYaw = glm::degrees(atan2(mDirection.z, mDirection.x));
}

void Camera::setSpeed(GLfloat newSpeed)
{
	mSpeed = newSpeed;
}

void Camera::setSensitivity(GLfloat newSensitivity)
{
	mSensitivity = newSensitivity;
}

void Camera::restoreZoom()
{
	mFOV = DEFAULT_FOV;
}

glm::vec3 Camera::getPosition() const
{
	return mPosition;
}

glm::vec3 Camera::getDirection() const
{
	return mDirection;
}

GLfloat Camera::getFOV() const
{
	return mFOV;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(mPosition, mPosition + mDirection, mUpAxis);
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::perspective(glm::radians(mFOV), (GLfloat)mWidth / (GLfloat)mHeight, 0.1f, 100.0f);
}

void Camera::updatePosition()
{
	if (mKeyboard->isKeyPressed(GLFW_KEY_W))
		mPosition += mSpeed * mDirection;

	if (mKeyboard->isKeyPressed(GLFW_KEY_S))
		mPosition -= mSpeed * mDirection;

	if (mKeyboard->isKeyPressed(GLFW_KEY_A))
		mPosition -= glm::normalize(glm::cross(mDirection, mUpAxis)) * mSpeed;

	if (mKeyboard->isKeyPressed(GLFW_KEY_D))
		mPosition += glm::normalize(glm::cross(mDirection, mUpAxis)) * mSpeed;
}

void Camera::updateDirection() 
{
	Point2D position = mMouse->getPointerPosition();

	if (mMouse->isButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && position.getY() < mHeight - 151 ) {

		//calculate displacement of mouse pointer
		GLfloat xoffset = static_cast<GLfloat>(position.getX() - mLastPointerPosition.getX());
		GLfloat yoffset = static_cast<GLfloat>(mLastPointerPosition.getY() - position.getY());

		//include sensitivity
		xoffset *= mSensitivity;
		yoffset *= mSensitivity;

		//update yaw and pitch angles
		mYaw += xoffset;
		mPitch += yoffset;

		//check for vertical boundaries 
		if (mPitch > 89.0f) 
			mPitch = 89.0f;
		else if (mPitch < -89.0f)
			mPitch = -89.0f;

		//calculate new direction vector from yaw and pitch angles
		glm::vec3 front;
		front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		front.y = sin(glm::radians(mPitch));
		front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		mDirection = glm::normalize(front);
	}

	//save last pointer position 
	mLastPointerPosition = position;
}

void Camera::updateZoom()
{
	if (mFOV >= 1.0f && mFOV <= DEFAULT_FOV)
		mFOV -= static_cast<GLfloat>(mMouse->getScrollWheelOffset());
	else if (mFOV < 1.0f)
		mFOV = 1.0f;
	else if (mFOV > DEFAULT_FOV)
		mFOV = DEFAULT_FOV;
}
