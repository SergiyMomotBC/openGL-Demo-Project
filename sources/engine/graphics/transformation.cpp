#include "transformation.h"

void Transformation::restorePosition()
{
	mPosition = glm::vec3(0.0f);
}

void Transformation::restoreAll()
{
	mPosition = glm::vec3(0.0f);
	mScale = glm::vec3(1.0f);
	mRotation = glm::vec3(0.0f);
}

glm::mat4 Transformation::getModelMatrix() const
{
	glm::mat4 model(1.0f);

	model = glm::translate(model, mPosition);
	model = glm::rotate(model, mRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, mRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, mRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, mScale);

	return model;
}

void Transformation::rotate(glm::vec3 newRotation)
{
	mRotation = newRotation;
}

void Transformation::rotateBy(float dx, float dy, float dz)
{
	mRotation += glm::vec3(dx, dy, dz);
}

void Transformation::rotateBy(glm::vec3 rotationVector)
{
	mRotation += rotationVector;
}

void Transformation::restoreRotation()
{
	mRotation = glm::vec3(0.0f);
}

void Transformation::restoreScale()
{
	mScale = glm::vec3(1.0f);
}

void Transformation::moveTo(float x, float y, float z)
{
	mPosition = glm::vec3(x, y, z);
}

void Transformation::moveTo(glm::vec3 newPosition)
{
	mPosition = newPosition;
}

void Transformation::moveBy(float dx, float dy, float dz)
{
	mPosition += glm::vec3(dx, dy, dz);
}

void Transformation::moveBy(glm::vec3 displacement)
{
	mPosition += displacement;
}

void Transformation::scale(float uniform)
{
	mScale = glm::vec3(uniform);
}

void Transformation::scale(float xScale, float yScale, float zScale)
{
	mScale = glm::vec3(xScale, yScale, zScale);
}

void Transformation::scale(glm::vec3 newScale)
{
	mScale = newScale;
}

void Transformation::scaleBy(float dx, float dy, float dz)
{
	mScale += glm::vec3(dx, dy, dz);
}

void Transformation::scaleBy(glm::vec3 scaleVector)
{
	mScale += scaleVector;
}

void Transformation::rotateX(float degrees)
{
	mRotation.x = degrees;
}

void Transformation::rotateY(float degrees)
{
	mRotation.y = degrees;
}

void Transformation::rotateZ(float degrees)
{
	mRotation.z = degrees;
}
