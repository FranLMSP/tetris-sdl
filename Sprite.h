#pragma once
#include "Graphics.h"
#include <iostream>
#include <string>

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}RedGreenBlue;

class Sprite
{
public:
	Sprite();
	Sprite(SDL_Renderer* ren, SDL_Rect* source, RedGreenBlue transPixels,std::string path);
	~Sprite();

	void loadTexture(SDL_Renderer* ren, RedGreenBlue colors);
	void draw(SDL_Renderer* ren);
	void drawFillDest(SDL_Renderer* ren);
	void drawPiece(SDL_Renderer*ren, SDL_Rect source, SDL_Rect dest);

	void setFillDest(SDL_Rect* fillDest);
	void setTransPixels(RedGreenBlue colors);
	void setSource(SDL_Rect* source);
	void setDest(SDL_Rect* dest);
	void setPath(std::string path);

	SDL_Rect* getFillDest();
	RedGreenBlue getTransPixels();
	SDL_Rect* getSource();
	SDL_Rect* getDest();
	std::string getPath();
	SDL_Texture* getTexture();

private:
	std::string _path;
	SDL_Rect* _source,* _dest,*_fillDest;
	RedGreenBlue _transPixels;
	SDL_Texture* _texture;
};
