#include "ui_contol_panel.h"

#include <vector>
#include "../engine/game/game.h"

void UIControlPanel::update()
{
	//decide what to display and which buttons are active
	if (!displayHelp) {
		if (!playAnimation) {
			translateButton.update();
			scaleButton.update();
			rotateButton.update();
			restoreButton.update();
		} else {
			//do the animation: 
			//translate in a circular path and rotate around Y axis such that draco is always looking at the center
			mModel->getTransform().moveTo(glm::sin(angle) * 25.0f, 0.0f, glm::cos(angle) * 25.0f);
			mModel->getTransform().rotateY(angle);

			//update angle of circular position
			angle += 0.01f;
			if (angle >= 360.f) angle = 0.0f;
		}

		animationButton.update();
		helpButton.update();

	} else {
		closeHelpButton.update();
	}
}

void UIControlPanel::startAnimation() {
	playAnimation = true;
	angle = 0.0f;
}

void UIControlPanel::stopAnimation() {
	playAnimation = false;
	mModel->getTransform().restoreAll();
	mModel->getTransform().scale(3.0f);
}

void UIControlPanel::render(const Renderer2D & renderer) const
{
	//draw all 2d ui stuff and text

	//panel
	renderer.renderSprite(panel, Point2D(0, 0), Dimension2D(Game::WIDTH, 151));
	renderer.renderText("Control Panel", font, Point2D(580, 127), Color(255, 255, 255));

	//header
	renderer.renderSprite(header, Point2D(430, 600), Dimension2D(420, 100));
	renderer.renderText("Assignment #1", font, Point2D(620, 650), Color(100, 100, 100));

	if (displayHelp) {
		renderer.renderSprite(helpBG, Point2D(388, 180), Dimension2D(500, 400));
		closeHelpButton.render(renderer);
		//render help text
		renderer.renderText("* W A S D - to move the camera", font, Point2D(450, 520), Color(255, 255, 255));
		renderer.renderText("* Hold LMB and move the mouse", font, Point2D(450, 495), Color(255, 255, 255));
		renderer.renderText("  - to change direction of camera", font, Point2D(450, 475), Color(255, 255, 255));
		renderer.renderText("* Scroll wheel - to zoom in/out camera", font, Point2D(450, 450), Color(255, 255, 255));
		renderer.renderText("* Hold X, Y or Z and click one of 3 buttons", font, Point2D(450, 400), Color(255, 255, 255));
		renderer.renderText("  to apply selected transformation", font, Point2D(450, 380), Color(255, 255, 255));
		renderer.renderText("* LMB - negative direction, RMB - positive", font, Point2D(450, 350), Color(255, 255, 255));
		renderer.renderText("* X Y Z can be pressed in combinations", font, Point2D(450, 325), Color(255, 255, 255));
		renderer.renderText("* Restore - clears all applied transformations", font, Point2D(450, 300), Color(255, 255, 255));
		renderer.renderText("* Animate - to start/stop animation", font, Point2D(450, 275), Color(255, 255, 255));
		renderer.renderText("* C - to restore camera position", font, Point2D(450, 250), Color(255, 255, 255));
	}

	//render buttons
	translateButton.render(renderer);
	renderer.renderText(translateButton.getText(), font, Point2D(220, 82), Color(255, 255, 255), -10.0f);

	scaleButton.render(renderer);
	renderer.renderText(scaleButton.getText(), font, Point2D(396, 73), Color(255, 255, 255), -5.0f);

	rotateButton.render(renderer);
	renderer.renderText(rotateButton.getText(), font, Point2D(538, 72), Color(255, 255, 255), -5.0f);

	animationButton.render(renderer);
	renderer.renderText(animationButton.getText(), font, Point2D(678, 67), Color(255, 255, 255), 5.0f);

	restoreButton.render(renderer);
	renderer.renderText(restoreButton.getText(), font, Point2D(826, 68), Color(255, 255, 255), 6.0f);

	helpButton.render(renderer);
	renderer.renderText(helpButton.getText(), font, Point2D(996, 70), Color(255, 255, 255), 10.0f);

	//watermark
	renderer.renderText("Sergiy Momot, Spring 2016", font, Point2D(20, 690), Color(255, 255, 255));
	renderer.renderText("CISC 3620, Prof. Levitan", font, Point2D(1030, 690), Color(255, 255, 255));
}

void UIControlPanel::setActions()
{
	//all buttons' actions are passed as lambda functions
	//which capture needed arguments 

	Model* temp = this->mModel;
	Mouse* ms = Input::getMouse();
	Keyboard* kb = Input::getKeyboard();

	translateButton.setOnClickAction([temp, ms, kb]() {
		
		auto m = ms->isButtonPressed(GLFW_MOUSE_BUTTON_LEFT) ? -1.0f : 1.0f;

		if(kb->isKeyPressed(GLFW_KEY_X))
			temp->getTransform().moveBy(m * 0.1f, 0.0f, 0.0f);
		if (kb->isKeyPressed(GLFW_KEY_Y))
			temp->getTransform().moveBy(0.0f, m * 0.1f, 0.0f);
		if (kb->isKeyPressed(GLFW_KEY_Z))
			temp->getTransform().moveBy(0.0f, 0.0f, m* 0.1f);
	});

	scaleButton.setOnClickAction([temp, ms, kb]() {

		auto m = ms->isButtonPressed(GLFW_MOUSE_BUTTON_LEFT) ? -1.0f : 1.0f;

		if (kb->isKeyPressed(GLFW_KEY_X))
			temp->getTransform().scaleBy(m * 0.1f, 0.0f, 0.0f);
		if (kb->isKeyPressed(GLFW_KEY_Y))
			temp->getTransform().scaleBy(0.0f, m * 0.1f, 0.0f);
		if (kb->isKeyPressed(GLFW_KEY_Z))
			temp->getTransform().scaleBy(0.0f, 0.0f, m* 0.1f);
	});

	rotateButton.setOnClickAction([temp, ms, kb]() {

		auto m = ms->isButtonPressed(GLFW_MOUSE_BUTTON_LEFT) ? -1.0f : 1.0f;

		if (kb->isKeyPressed(GLFW_KEY_X))
			temp->getTransform().rotateBy(m * 0.1f, 0.0f, 0.0f);
		if (kb->isKeyPressed(GLFW_KEY_Y))
			temp->getTransform().rotateBy(0.0f, m * 0.1f, 0.0f);
		if (kb->isKeyPressed(GLFW_KEY_Z))
			temp->getTransform().rotateBy(0.0f, 0.0f, m* 0.1f);
	});

	animationButton.setOnClickAction([this]() {
		if(!this->getAnimButton().isPressed())
			if (!this->isAnimationPlaying()) 
				this->startAnimation();
			else  
				this->stopAnimation();
	});

	restoreButton.setOnClickAction([temp]() {
		temp->getTransform().restoreAll();
		temp->getTransform().scale(3.0f);
	});

	helpButton.setOnClickAction([this]() {
		this->showHelp();
	});

	closeHelpButton.setOnClickAction([this]() {
		this->hideHelp();
	});
}


