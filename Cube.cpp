#include "Cube.h"

Cube::Cube(Color color,char x,char y, int xdest, int ydest)
{
	this->_xdest = xdest; this->_ydest = ydest;
	this->_setType(SOLID);
	this->setX(x);
	this->setY(y);
	this->_setDest(xdest, ydest);
	this->_cube.dest.w = 22; this->_cube.dest.h = 22;
	this->_setColor(color);
}


Cube::Cube()
{
	this->_setType(NONE);
}
Cube::Cube(Cube*clone)
{
	Cube *rtn = new Cube();
	this->_cube.x = clone->_cube.x;
	this->_cube.y = clone->_cube.y;
	this->_xdest = clone->_xdest;
	this->_ydest = clone->_ydest;
	this->_cube.source = clone->_cube.source;
	this->_cube.dest = clone->_cube.dest;
	this->_cube.color = clone->_cube.color;
	this->_cube.type = clone->_cube.type;
}

void Cube::setX(char x)
{
	this->_cube.x = x;
}
void Cube::setY(char y)
{
	this->_cube.y = y;
}
char Cube::getX()
{
	return this->_cube.x;
}
char Cube::getY()
{
	return this->_cube.y;
}

void Cube::_setSource(SDL_Rect source)
{
	this->_cube.source = source;
}
void Cube::_setDest(char destx,char desty)
{
	this->_cube.dest.x = (this->getX()*22)+destx;
	this->_cube.dest.y = (this->getY()*22)+desty;
}

SDL_Rect Cube::getSource()
{
	return this->_cube.source;
}
SDL_Rect Cube::getDest()
{
	return this->_cube.dest;
}

void Cube::update()
{
	this->_setDest(this->_xdest, this->_ydest);
}

void Cube::_setColor(Color color)
{
	//enum Color { BLUE, YELLOW, MAGENTA, GREEN, CYAN, RED, ORANGE };
	this->_cube.color = color;
	switch (color)
	{
		case BLUE: this->_setSource({ 0,0,22,22 }); break;
		case YELLOW: this->_setSource({ 23,0,22,22 }); break;
		case MAGENTA: this->_setSource({ 46,0,22,22 }); break;
		case GREEN: this->_setSource({ 69,0,22,22 }); break;
		case CYAN: this->_setSource({ 92,0,22,22 }); break;
		case RED: this->_setSource({ 115,0,22,22 }); break;
		case ORANGE: this->_setSource({ 138,0,22,22 }); break;
	}
}

bool Cube::collision(CubeStruct cube)
{
	if ((this->getX() == cube.x && this->getY() == cube.y) && (cube.type==SOLID))
	{
		return true;

	}
	return false;
}

bool Cube::upper()
{
	if (this->getY() < 0)
	{
		return true;
	}
	return false;
}

CubeStruct Cube::getCube()
{
	return this->_cube;
}

bool Cube::borderLeft()
{
	if (this->getX() < 0)
	{
		return true;
	}
	return false;
}
bool Cube::borderRight()
{
	if (this->getX() > 9)
	{
		return true;
	}
	return false;
}

bool Cube::falled()
{
	if (this->getY() > 19)
	{
		return true;
	}
	return false;
}

void Cube::_setType(Type type)
{
	this->_cube.type = type;
}
Type Cube::getType()
{
	return this->_cube.type;
}

void Cube::draw(SDL_Renderer*ren, Sprite* sprite)
{
	sprite->drawPiece(ren, this->getSource(), this->getDest());
}

void Cube::up()
{
	this->_cube.y--;
	this->update();
}
void Cube::down()
{
	this->_cube.y++;
	this->update();
}
void Cube::left()
{
	this->_cube.x--;
	this->update();
}
void Cube::right()
{
	this->_cube.x++;
	this->update();
}

Cube::~Cube()
{
}
