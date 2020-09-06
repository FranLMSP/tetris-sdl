#include "Sprite.h"
#include <string.h>


Sprite::Sprite()
{
	this->_texture = nullptr;
	SDL_Rect r = { 0,0,0,0 };
	this->setDest(&r);
	this->setSource(&r);
	this->setFillDest(&r);
	this->setPath("res/blank.bmp");
	this->setTransPixels({ 0,0,0 });

}

Sprite::Sprite(SDL_Renderer* ren,SDL_Rect* source, RedGreenBlue transPixels, std::string path)
{
	this->_texture = nullptr;
	this->setSource(source);
	this->setTransPixels(transPixels);
	this->setPath(path);

	this->loadTexture(ren, transPixels);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(this->getTexture());
	std::cout << "Sprite destroyed" << std::endl;
}

void Sprite::draw(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, this->getTexture(), this->getSource(), this->getDest());
	//SDL_RenderCopy(ren, this->getTexture(), NULL, &this->_dest);
}

void Sprite::drawPiece(SDL_Renderer*ren, SDL_Rect source, SDL_Rect dest)
{
	SDL_RenderCopy(ren, this->getTexture(), &source, &dest);
}

void Sprite::drawFillDest(SDL_Renderer* ren)
{
	SDL_RenderSetClipRect(ren, this->getFillDest());
	SDL_RenderCopy(ren, this->getTexture(), this->getSource(), this->getDest());
}


void Sprite::loadTexture(SDL_Renderer* ren, RedGreenBlue colors)
{
	std::string ruta = std::string(SDL_GetBasePath());
	ruta = ruta + this->getPath();
	SDL_Surface* bmp = Graphics::loadBMP(ruta);
	if (SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, colors.r, colors.g, colors.b) ) != 0)
	{
		std::cout << "Error setting color key: " << SDL_GetError();
	}
	this->_texture = Graphics::CreateTexture(ren, bmp);
	//SDL_FreeSurface(bmp);
	std::cout << "BMP loaded" << std::endl;
}

void Sprite::setFillDest(SDL_Rect* fillDest)
{
	this->_fillDest = fillDest;
}
void Sprite::setTransPixels(RedGreenBlue colors)
{
	this->_transPixels = colors;
}
void Sprite::setSource(SDL_Rect* source)
{
	this->_source = source;
}
void Sprite::setDest(SDL_Rect* dest)
{
	this->_dest = dest;
}
void Sprite::setPath(std::string path)
{
	this->_path = path;
}

SDL_Rect* Sprite::getFillDest()
{
	return this->_fillDest;
}
RedGreenBlue Sprite::getTransPixels()
{
	return this->_transPixels;
}
SDL_Rect* Sprite::getSource()
{
	return this->_source;
}
SDL_Rect*Sprite::getDest()
{
	return this->_dest;
}
std::string Sprite::getPath()
{
	return this->_path;
}
SDL_Texture* Sprite::getTexture()
{
	return this->_texture;
}