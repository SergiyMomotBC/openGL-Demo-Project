#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>
#include "../sources/engine/geometry/dimension_2d.h"
#include "../sources/engine/geometry/point_2d.h"
#include "../sources/engine/graphics/texture.h"
#include "../sources/engine/graphics/renderer_2d.h"
#include "../sources/engine/input/input_system.h"

class Button
{
public:
	/* Creates a button with given attributes and textures. */
	Button(const std::string& text,
		   const std::string& image,
		   const std::string& imagePressed,
		   const std::string& imageOnMouse,
		   const Point2D& position, 
		   const Dimension2D& size)
		: mText(text), mImage(image), mImagePressed(imagePressed), mImageOnMouse(imageOnMouse), 
		  mIsPressed(false), mIsOnMouse(false), mPositon(position), mSize(size) 
	{}

	/* Draws button to the screen. */
	void render(const Renderer2D& renderer) const;

	/* Checks button's events. */
	void update();

	/* Position setter. */
	void setPosition(const Point2D& newPosition) { mPositon = newPosition; }

	/* Size setter. */
	void setSize(const Dimension2D& newSize) { mSize = newSize; }

	/* Text setter. */
	void setText(const std::string& newText) { mText = newText; }

	/* Position getter. */
	Point2D getPosition() const { return mPositon; }

	/* Size getter. */
	Dimension2D getSize() const { return mSize; }

	/* Text getter. */
	std::string getText() const { return mText; }

	/* Sets an action to be executed when the button is clicked. */
	void setOnClickAction(std::function<void()> action) { mAction = action; }

	/* Checks if button is currently pressed. */
	bool isPressed() const { return mIsPressed; }

private:
	std::string mText;

	Point2D mPositon;
	Dimension2D mSize;

	Texture mImage;
	Texture mImagePressed;
	Texture mImageOnMouse;

	bool mIsPressed;
	bool mIsOnMouse;

	std::function<void()> mAction;
};

#endif 
