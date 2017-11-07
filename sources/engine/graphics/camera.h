#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../sources/engine/input/input_system.h"
#include "../sources/engine/geometry/point_2d.h"

#define DEFAULT_FOV 60.0f

class Camera
{
public:
	/* Creates 3D camera for given resolution, field of view, starting position. */
	Camera(int width, int height, GLfloat fov = DEFAULT_FOV, glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f));

	/* Per frame update from input devices. */
	void update(double dt);

	/* Position setter. */
	void setPosition(glm::vec3 newPosition);

	/* Direction setter. */
	void setDirection(glm::vec3 newDirection);

	/* Set direction to a specific point in 3d space. */
	void lookAtPoint(glm::vec3 point);

	/* Movement speed setter. */
	void setSpeed(GLfloat newSpeed);

	/* Camera sensativity to mouse movement setter. */
	void setSensitivity(GLfloat newSensitivity);

	/* Sets default zoom. */
	void restoreZoom();

	/* Position getter. */
	glm::vec3 getPosition() const;

	/* Direction getter. */
	glm::vec3 getDirection() const;

	/* Field of view getter. */
	GLfloat getFOV() const;

	/* Return View matrix. */
	glm::mat4 getViewMatrix() const;

	/* Return perspective Projection matrix. */
	glm::mat4 getProjectionMatrix() const;

	//no copy allowed
	Camera(const Camera& nocopy) = delete;
	Camera& operator=(const Camera& nocopy) = delete;

	/* Empty destructor. */
	virtual ~Camera() {}

private:
	glm::vec3 mPosition;
	glm::vec3 mDirection;
	glm::vec3 mUpAxis;

	Point2D mLastPointerPosition;

	GLfloat mYaw;
	GLfloat mPitch;

	GLfloat mFOV;

	GLfloat mSpeed;
	GLfloat mSensitivity;

	int mWidth;
	int mHeight;

	//not owner 
	Keyboard* mKeyboard;
	Mouse* mMouse;

	void updatePosition();
	void updateDirection();
	void updateZoom();
};

#endif
