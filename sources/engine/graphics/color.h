#ifndef COLOR_H
#define COLOR_H

#include "glm/glm.hpp"

class Color
{
public:
	/* Default constructor. Black color. */
	Color() : mRed(0.0f), mGreen(0.0f), mBlue(0.0f), mAlpha(1.0f) {}

	/* Constructor with RGBA float components. */
	Color(float red, float green, float blue, float alpha = 1.0f)
		: mRed(red), mGreen(green), mBlue(blue), mAlpha(alpha) {}

	/* Constructor with RGBA int(0..255) components. */
	Color(int red, int green, int blue, int alpha = 255)
		: mRed(red / 255.0f), mGreen(green / 255.0f), mBlue(blue / 255.0f), mAlpha(alpha / 255.0f) {}

	/* Get GLM vector representing current color. */
	glm::vec4 getColorVector() const { return glm::vec4(mRed, mGreen, mBlue, mAlpha); }

	/* Red channel getter. */
	float getRedChannel() const { return mRed;  }

	/* Green channel getter. */
	float getGreenChannel() const { return mGreen; }

	/* Blue channel getter. */
	float getBlueChannel() const { return mBlue; }

	/* Alpha channel getter. */
	float getAlphaChannel() const { return mAlpha; }

	/* Empty destructor. */
	virtual ~Color() {}

private:
	float mRed;
	float mGreen;
	float mBlue;
	float mAlpha;
};

#endif
