#pragma once
#include <SDL2/SDL.h>

#include <map>

class Input
{
public:
	Input();
	void beginNewFrame();
	void KeyUpEvent();
	void KeyDownEvent();

	void pollEvent();

	void setKeyUP(SDL_Scancode key);
	void setKeyDOWN(SDL_Scancode key);
	void setKeyLEFT(SDL_Scancode key);
	void setKeyRIGHT(SDL_Scancode key);
	void setKeyA(SDL_Scancode key);
	void setKeyB(SDL_Scancode key);
	void setKeySTART(SDL_Scancode key);
	void setKeySELECT(SDL_Scancode key);

	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);

	bool isUpPressed();
	bool isDownPressed();
	bool isLeftPressed();
	bool isRightPressed();
	bool isAPressed();
	bool isBPressed();
	bool isSelectPressed();
	bool isStartPressed();

	bool isUpHeld();
	bool isDownHeld();
	bool isLeftHeld();
	bool isRightHeld();
	bool isAHeld();
	bool isBHeld();
	bool isSelectHeld();
	bool isStartHeld();
	bool quit();

private:
	std::map<SDL_Scancode, bool>_heldKeys;
	std::map<SDL_Scancode, bool>_relKeys;
	std::map<SDL_Scancode, bool>_pressedKeys;
	std::map<SDL_Scancode, bool>_releasedKeys;

	SDL_Scancode _up, _down, _left, _right, _a, _b, _start,_select;
	bool _quit = false;

	SDL_Event _event;

};
