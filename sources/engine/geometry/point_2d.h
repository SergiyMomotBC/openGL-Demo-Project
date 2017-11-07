#ifndef POINT2D_H
#define POINT2D_H

#include "glm/glm.hpp"

class Point2D
{
public:
	/* Default constructor. */
	Point2D() : mX(0.0), mY(0.0) {};

	/* Creates a point with given coordinates. */
	Point2D(double x, double y) : mX(x), mY(y) {};

	/* Creates a point from the given vector. */
	Point2D(glm::vec2 coordinates) : mX(coordinates.x), mY(coordinates.y) {}

	/* Returns a displacement vector calculated by the subtraction operator. */
	glm::vec2 operator-(const Point2D& point) { 
		return glm::vec2(mX - point.mX, mY - point.mY);
	}

	/* X coordinate getter. */
	double getX() const { return mX; }

	/* Y coordinate getter. */
	double getY() const { return mY; }

	/* X coordinate setter. */
	void setX(double newX) { mX = newX; }

	/* Y coordinate setter. */
	void setY(double newY) { mY = newY; }

	/* Sets new point coordinates. */
	void update(double newX, double newY) {
		mX = newX;
		mY = newY;
	}

	/* Returns 2d vector representing a point. */
	glm::vec2 getVectorForm() const { return glm::vec2(mX, mY); }

	/* Destructor. */
	virtual ~Point2D() {};

private:
	double mX;
	double mY;
};

#endif

