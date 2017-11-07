#include "button.h"

#include "../sources/engine/game/game.h"

void Button::render(const Renderer2D & renderer) const
{
	renderer.renderSprite( mIsPressed ? mImagePressed : (mIsOnMouse ? mImageOnMouse : mImage), mPositon, mSize );
}

void Button::update()
{
	Mouse* mouse = Input::getMouse();
	auto mouse_pos = mouse->getPointerPosition();
	
	//invert mouse Y coordinate (so far GLFW and my engine use different 2D coordinate systems)
	mouse_pos.setY(Game::HEIGHT - mouse_pos.getY());

	//check if point (mouse pointer position) is inside rectangle formed by button edges
	bool inside = (mouse_pos.getX() > mPositon.getX()) && (mouse_pos.getX() < mPositon.getX() + mSize.getWidth()) &&
		(mouse_pos.getY() > mPositon.getY()) && (mouse_pos.getY() < mPositon.getY() + mSize.getHeight());

	//if inside then button is either clicked (if mouse button is pressed) or just onMouse event
	if (inside)
		if (mouse->isButtonPressed(GLFW_MOUSE_BUTTON_LEFT) || mouse->isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			//run onClick event
			mAction();
			mIsPressed = true;
		} else
			mIsOnMouse = true;
	else
		mIsOnMouse = false;

	//stop being clicked
	if (!inside && mIsPressed)
		mIsPressed = false;

	if (inside && mouse->isButtonReleased(GLFW_MOUSE_BUTTON_LEFT))
		mIsPressed = false;

}
