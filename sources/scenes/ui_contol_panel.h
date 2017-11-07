#ifndef UI_CONTROL_PANEL_H
#define UI_CONTROL_PANEL_H

#include "../engine/ui/button.h"
#include "../engine/graphics/renderer_2d.h"
#include "../sources/engine/graphics/model.h"

class UIControlPanel
{
public:
	UIControlPanel(Model* controlledModel)
		: translateButton("Translate", "assets/ui/but1_norm.png", "assets/ui/but1_onpress.png", "assets/ui/but1_onmouse.png", Point2D(175, 31), Dimension2D(182, 95)),
		scaleButton("Scale", "assets/ui/but2_norm.png", "assets/ui/but2_onpress.png", "assets/ui/but2_onmouse.png", Point2D(345, 37), Dimension2D(156, 72)),
		rotateButton("Rotate", "assets/ui/but3_norm.png", "assets/ui/but3_onpress.png", "assets/ui/but3_onmouse.png", Point2D(494, 38), Dimension2D(156, 67)),
		animationButton("Animate", "assets/ui/but4_norm.png", "assets/ui/but4_onpress.png", "assets/ui/but4_onmouse.png", Point2D(635, 38), Dimension2D(152, 67)),
		restoreButton("Restore", "assets/ui/but5_norm.png", "assets/ui/but5_onpress.png", "assets/ui/but5_onmouse.png", Point2D(783, 36), Dimension2D(153, 74)),
		helpButton("Help", "assets/ui/but6_norm.png", "assets/ui/but6_onpress.png", "assets/ui/but6_onmouse.png", Point2D(928, 31), Dimension2D(176, 95)),
		closeHelpButton("", "assets/ui/close_button.png", "assets/ui/close_button.png", "assets/ui/close_button_pr.png", Point2D(380, 534), Dimension2D(38, 36)),
		font("assets/fonts/arial.ttf", 20),
		panel("assets/ui/panel.png"),
		header("assets/ui/header.png"),
		helpBG("assets/ui/help_bg.png"),
		mModel(controlledModel),
		displayHelp(false),
		playAnimation(false),
		angle(0.0f)
	{
		setActions();
	}

	//update logic
	void update();

	//display Help Window
	void showHelp() { displayHelp = true; }
	void hideHelp() { displayHelp = false; }

	//start and stop playing animation
	void startAnimation();
	void stopAnimation();
	
	//for lambda access
	Button& getAnimButton() { return animationButton; }

	//to check if animation is playing 
	bool isAnimationPlaying() const { return playAnimation; }

	//render ui
	void render(const Renderer2D& renderer) const;

	virtual ~UIControlPanel() {}

private:
	Button translateButton;
	Button scaleButton;
	Button rotateButton;
	Button animationButton;
	Button restoreButton;
	Button helpButton;
	Button closeHelpButton;

	Font font;

	Texture panel;
	Texture header;
	Texture helpBG;

	Model* mModel;

	bool displayHelp;
	bool playAnimation;

	float angle;

	void setActions();
};

#endif 
