#ifndef GAME_SCENE_H
#define GAME_SCENE_H

/* Interface for creating game scenes. */
class IGameScene
{
public:
	/* Called when scene is created. */
	virtual void onStart() = 0;

	/* Called every frame when active for all logic updates. */
	virtual void onUpdate(double dt) = 0;

	/* Called every time the rendering will happen. */
	virtual void onRender() = 0;

	/* Called when scene is destroyed. */
	virtual void onClose() = 0;

	/* Optional. Called when scene becomes inactive for a moment. */
	virtual void onPause() {}

	/* Optional. Called when scene becomes active again. */
	virtual void onResume() {}

	/* Destructor. */
	virtual ~IGameScene() {}
};

#endif 

