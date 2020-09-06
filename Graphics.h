#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class Graphics
{
public:
	Graphics();
	~Graphics();

	static SDL_Surface* loadBMP(std::string path);
	static SDL_Texture* CreateTexture(SDL_Renderer* ren, SDL_Surface* bmp);

	void clear();
	void blitSurface(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* source, SDL_Rect* dest);
	void draw();

	void init();

	SDL_Window* getWindow();
	SDL_Surface*getSurface();
	SDL_Renderer* getRenderer();


private:

	void createWindow();
	void createRenderer();

	SDL_Window* _window;
	SDL_Surface* _screenSurface;
	SDL_Renderer* _renderer;

	int _windowW=640, _windowH=480;
};
