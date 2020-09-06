#include "Graphics.h"



Graphics::Graphics()
{
	this->_window = nullptr;
	this->_screenSurface = nullptr;
	this->_renderer = nullptr;
}


Graphics::~Graphics()
{
	SDL_DestroyWindow(this->getWindow());
	SDL_DestroyRenderer(this->getRenderer());

	std::cout << "GRAPHICS CLASS DESTROYED" << std::endl;
}

void Graphics::init()
{
	this->createWindow();
	this->createRenderer();
}

void Graphics::createWindow()
{
	this->_window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->_windowW, this->_windowH, SDL_WINDOW_OPENGL);
	if (this->_window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
	}
}

void Graphics::createRenderer()
{
	this->_renderer = SDL_CreateRenderer(this->_window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (this->_renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	}
}

SDL_Surface* Graphics::loadBMP(std::string path)
{
	SDL_Surface * bmp = nullptr;
	bmp = SDL_LoadBMP(path.c_str());
	std::cout << path << std::endl;
	if (bmp == nullptr)
	{
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
	}
	return bmp;
}

SDL_Texture* Graphics::CreateTexture(SDL_Renderer* ren, SDL_Surface* bmp)
{
	SDL_Texture* texture = nullptr;
	texture = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (texture == nullptr)
	{
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}

void Graphics::clear()
{
	SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 0);
	SDL_RenderClear(this->getRenderer());
}

void Graphics::blitSurface(SDL_Renderer* renderer,SDL_Texture* texture,SDL_Rect* source, SDL_Rect* dest)
{		
	SDL_RenderCopy(renderer, texture, source, dest);
}

void Graphics::draw()
{	
	SDL_RenderPresent(this->getRenderer());
}

SDL_Renderer* Graphics::getRenderer()
{
	return this->_renderer;
}

SDL_Window* Graphics::getWindow()
{
	return this->_window;
}

SDL_Surface* Graphics::getSurface()
{
	return this->_screenSurface;
}