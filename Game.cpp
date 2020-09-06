#include "Game.h"
Game::Game()
{
	this->_graphics = new Graphics();
	this->_gameState = INGAME;
}

Game::~Game()
{
	this->_graphics->~Graphics();
	SDL_Quit();
	std::cout << "GAME CLASS DESTROYED" << std::endl;
	exit(0);

}

void Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
	this->_timer.setFps(60);
	this->_graphics->init();
	this->_inGame = new InGame(this->_graphics->getRenderer(),20,20);
	//this->_sprite = new Sprite(this->_graphics->getRenderer(),NULL, { 0,0,0 }, "res/face.bmp");

	this->gameLoop();
}

void Game::menuLoop()
{

}

void Game::pauseLoop()
{

}

void Game::frameStart()
{
	this->_timer.start();
	this->readInputs();
}

void Game::frameEnd()
{
	this->_graphics->clear();

	//DRAW SPRITE
	this->_inGame->draw(this->_graphics->getRenderer());

	this->_graphics->draw();
	this->_timer.delay();
}

void Game::readInputs()
{
	this->_input.beginNewFrame();
	this->_input.pollEvent();

/*	if (this->_input.isUpHeld())
	{
		std::cout << "UP HELD" << std::endl;
	}
	if (this->_input.isDownHeld())
	{
		std::cout << "DOWN HELD" << std::endl;
	}
	if (this->_input.isLeftHeld())
	{
		std::cout << "LEFT HELD" << std::endl;
	}
	if (this->_input.isRightHeld())
	{
		std::cout << "RIGHT HELD" << std::endl;
	}
	if (this->_input.isAHeld())
	{
		std::cout << "A HELD" << std::endl;
	}
	if (this->_input.isBHeld())
	{
		std::cout << "B HELD" << std::endl;
	}*/
	if (this->_input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
	{
		std::cout << "ESCAPE PRESSED" << std::endl;
	}
	if (this->_input.wasKeyPressed(SDL_SCANCODE_A))
	{
		//std::cout << "A PRESSED" << std::endl;
		this->_inGame->keyLeft();
	}
	if (this->_input.wasKeyPressed(SDL_SCANCODE_D))
	{
		//std::cout << "D PRESSED" << std::endl;
		this->_inGame->keyRight();
	}
	if (this->_input.isDownHeld())
	{
		this->_inGame->heldDown();
	}
	if (this->_input.wasKeyReleased(SDL_SCANCODE_S))
	{
		this->_inGame->releasedDown();
	}
	if (this->_input.wasKeyPressed(SDL_SCANCODE_K))
	{
		//std::cout << "ROTATE RIGHT" << std::endl;
		this->_inGame->keyRotateR();
	}
	if (this->_input.wasKeyPressed(SDL_SCANCODE_J))
	{
		//std::cout << "ROTATE LEFT" << std::endl;
		this->_inGame->keyRotateL();
	}

	if (this->_input.quit())
	{
		this->~Game();
	}
}

void Game::gameLoop()
{
	while (this->_gameState==INGAME)
	{
		this->frameStart();

		this->_inGame->update();

		this->frameEnd();
	}
}
