#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Transformation
{
public:
	/* Default constructor. */
	Transformation() 
		: mPosition(0.0f), mScale(1.0f), mRotation(0.0f) {}

	/* Creates a transform with a starting position. */
	Transformation(glm::vec3 position) 
		: mPosition(position), mScale(1.0f), mRotation(0.0f) {}

	/* Creates a transform with a starting position and scale. */
	Transformation(glm::vec3 position, glm::vec3 scale) 
		: mPosition(position), mScale(scale), mRotation(0.0f) {}

	/* Creates a transform with a starting position, scale and rotation.  */
	Transformation(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) 
		: mPosition(position), mScale(scale), mRotation(rotation) {}
	
	/* Sets position to a given coordinates. */
	void moveTo(float x, float y, float z = 0.0f);

	/* Sets position to a given point represented by a vector. */
	void moveTo(glm::vec3 newPosition);

	/* Changes the position by a given delta coordinates. */
	void moveBy(float dx, float dy, float dz);

	/* Changes the position by a given displacement vector.  */
	void moveBy(glm::vec3 displacement);

	/* Uniformly sets a scale by a given factor. */
	void scale(float uniform);

	/* Sets a scale by given axis factors. */
	void scale(float xScale, float yScale, float zScale = 1.0f);

	/* Sets a scale by a given scale vector. */
	void scale(glm::vec3 newScale);

	/* Changes scale by a given delta factors. */
	void scaleBy(float dx, float dy, float dz);

	/* Changes scale by a given delta vector. */
	void scaleBy(glm::vec3 scaleVector);

	/* Sets rotation over X axis. */
	void rotateX(float degrees);

	/* Sets rotation over Y axis. */
	void rotateY(float degrees);

	/* Sets rotation over Z axis. */
	void rotateZ(float degrees);

	/* Sets rotation from a given rotation vector of degrees over all axis. */
	void rotate(glm::vec3 newRotation);

	/* Changes rotation by given delta angles over all axis. */
	void rotateBy(float dx, float dy, float dz);

	/* Changes rotation by given delta rotation vector of degrees over all axis. */
	void rotateBy(glm::vec3 rotationVector);

	/* Sets rotation to over all axis to 0 degrees. */
	void restoreRotation();

	/* Sets scale to 1 for all components. */
	void restoreScale();

	/* Sets position to origin (0, 0, 0). */
	void restorePosition();

	/* Sets all transformations to their default values. */
	void restoreAll();

	/* Returns a model matrix representing all transforms combined into one 4x4 matrix. */
	glm::mat4 getModelMatrix() const;

	/* Empty destructor. */
	virtual ~Transformation() {}

private:
	glm::vec3 mPosition;
	glm::vec3 mScale;
	glm::vec3 mRotation;
};

#endif
