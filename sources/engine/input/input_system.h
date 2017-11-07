#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "mouse.h"
#include "keyboard.h"
#include "../sources/engine/windowing/window.h"

/* Input system. */
class Input final
{
public:
	/* Starts the input system. */
	static void startUp(const Window& eventSource) {
		sMouseDevice = new Mouse(eventSource);
		sKeyboardDevice = new Keyboard(eventSource);
	}

	/* Returns mouse pointer. */
	static Mouse* getMouse() { return sMouseDevice; }

	/* Returns keyboard pointer. */
	static Keyboard* getKeyboard() { return sKeyboardDevice; }

	/* Stops the input system. */
	static void shutDown() {
		delete sMouseDevice;
		delete sKeyboardDevice;
	}

private:
	Input() {}

	static Mouse* sMouseDevice;
	static Keyboard* sKeyboardDevice;
};

#endif
