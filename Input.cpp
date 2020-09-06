#include "Input.h"


Input::Input()
{
	this->setKeyUP(SDL_SCANCODE_W);
	this->setKeyDOWN(SDL_SCANCODE_S);
	this->setKeyLEFT(SDL_SCANCODE_A);
	this->setKeyRIGHT(SDL_SCANCODE_D);
	this->setKeyA(SDL_SCANCODE_K);
	this->setKeyB(SDL_SCANCODE_J);
	this->setKeySTART(SDL_SCANCODE_N);
	this->setKeySELECT(SDL_SCANCODE_B);
}

void Input::beginNewFrame()
{
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}

void Input::KeyDownEvent()
{
	this->_pressedKeys[this->_event.key.keysym.scancode] = true;
	this->_heldKeys[this->_event.key.keysym.scancode] = true;
}

void Input::KeyUpEvent()
{
	this->_releasedKeys[this->_event.key.keysym.scancode] = true;
	this->_heldKeys[this->_event.key.keysym.scancode] = false;
}

bool Input::wasKeyPressed(SDL_Scancode key)
{
	return this->_pressedKeys[key];
}

bool Input::wasKeyReleased(SDL_Scancode key)
{
	return this->_releasedKeys[key];
}

bool Input::isKeyHeld(SDL_Scancode key)
{
	return this->_heldKeys[key];
}


bool Input::isUpPressed() { return this->wasKeyPressed(this->_up); }
bool Input::isDownPressed() { return this->wasKeyPressed(this->_down); }
bool Input::isLeftPressed() { return this->wasKeyPressed(this->_left); }
bool Input::isRightPressed() { return this->wasKeyPressed(this->_right); }
bool Input::isAPressed() { return this->wasKeyPressed(this->_a); }
bool Input::isBPressed() { return this->wasKeyPressed(this->_b); }
bool Input::isSelectPressed() { return this->wasKeyPressed(this->_select); }
bool Input::isStartPressed() { return this->wasKeyPressed(this->_start); }

bool Input::isUpHeld() { return this->isKeyHeld(this->_up); }
bool Input::isDownHeld() { return this->isKeyHeld(this->_down); }
bool Input::isLeftHeld() { return this->isKeyHeld(this->_left); }
bool Input::isRightHeld() { return this->isKeyHeld(this->_right); }
bool Input::isAHeld() { return this->isKeyHeld(this->_a); }
bool Input::isBHeld() { return this->isKeyHeld(this->_b); }
bool Input::isSelectHeld() { return this->isKeyHeld(this->_select); }
bool Input::isStartHeld() { return this->isKeyHeld(this->_start); }
bool Input::quit() { return this->_quit; }


void Input::setKeyUP(SDL_Scancode key)
{
	this->_up = key;
}
void Input::setKeyDOWN(SDL_Scancode key)
{
	this->_down = key;
}
void Input::setKeyLEFT(SDL_Scancode key)
{
	this->_left = key;
}
void Input::setKeyRIGHT(SDL_Scancode key)
{
	this->_right = key;
}
void Input::setKeyA(SDL_Scancode key)
{
	this->_a = key;
}
void Input::setKeyB(SDL_Scancode key)
{
	this->_b = key;
}
void Input::setKeySTART(SDL_Scancode key)
{
	this->_start = key;
}
void Input::setKeySELECT(SDL_Scancode key)
{
	this->_select = key;
}

void Input::pollEvent()
{
	if (SDL_PollEvent(&this->_event))
	{
		if (this->_event.type == SDL_KEYDOWN)
		{
			if (this->_event.key.repeat == 0)
			{
				this->KeyDownEvent();
			}
		}
		else
		if (this->_event.type == SDL_KEYUP)
		{
			this->KeyUpEvent();
		}
		else
		if (this->_event.type == SDL_QUIT)
		{
			this->_quit = true;
		}
	}
}
