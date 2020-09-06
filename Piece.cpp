#include "Piece.h"
#include <math.h>

Piece::Piece(Color color,char x,char y, int xdest, int ydest)
{
	//BLUE,YELLOW,MAGENTA,GREEN,CYAN,RED,ORANGE
	this->color = color;
	switch (color)
	{
		case BLUE:this->_setBlue(x, y, xdest, ydest); break;
		case YELLOW:this->_setYellow(x, y, xdest, ydest); break;
		case MAGENTA:this->_setMagenta(x, y, xdest, ydest); break;
		case GREEN:this->_setGreen(x, y, xdest, ydest); break;
		case CYAN:this->_setCyan(x, y, xdest, ydest); break;
		case RED:this->_setRed(x, y, xdest, ydest); break;
		case ORANGE:this->_setOrange(x, y, xdest, ydest); break;
	}
}

Piece::Piece()
{
}

void Piece::_setBlue(char x, char y, int xdest, int ydest)
{
	this->_cubes[0] = new Cube(BLUE,x,y,xdest,ydest);
	this->_cubes[1] = new Cube(BLUE, x, y+1, xdest, ydest);
	this->_cubes[2] = new Cube(BLUE, x+1, y+1, xdest, ydest);
	this->_cubes[3] = new Cube(BLUE, x+2, y+1, xdest, ydest);
	this->_pivotX = x+1; this->_pivotY = y+1;
}

void Piece::_setYellow(char x,char y, int xdest, int ydest)
{
	this->_cubes[0] = new Cube(YELLOW, x, y, xdest, ydest);
	this->_cubes[1] = new Cube(YELLOW, x+1, y, xdest, ydest);
	this->_cubes[2] = new Cube(YELLOW, x, y+1, xdest, ydest);
	this->_cubes[3] = new Cube(YELLOW, x+1, y+1, xdest, ydest);
	this->_pivotX = x+0; this->_pivotY = y+0;
}

void Piece::_setMagenta(char x,char y, int xdest, int ydest)
{
	this->_cubes[0] = new Cube(MAGENTA, x, y+1, xdest, ydest);
	this->_cubes[1] = new Cube(MAGENTA, x+1, y, xdest, ydest);
	this->_cubes[2] = new Cube(MAGENTA, x+1, y+1, xdest, ydest);
	this->_cubes[3] = new Cube(MAGENTA, x+2, y+1, xdest, ydest);
	this->_pivotX = x+1; this->_pivotY = y+1;
}
void Piece::_setGreen(char x,char y, int xdest, int ydest)
{
	this->_cubes[0] = new Cube(GREEN, x, y, xdest, ydest);
	this->_cubes[1] = new Cube(GREEN, x+1, y, xdest, ydest);
	this->_cubes[2] = new Cube(GREEN, x-1, y+1, xdest, ydest);
	this->_cubes[3] = new Cube(GREEN, x, y+1, xdest, ydest);
	this->_pivotX = x+0; this->_pivotY = y+1;
}
void Piece::_setCyan(char x,char y, int xdest, int ydest)
{
	this->_cubes[0] = new Cube(CYAN, x, y, xdest, ydest);
	this->_cubes[1] = new Cube(CYAN, x, y+1, xdest, ydest);
	this->_cubes[2] = new Cube(CYAN, x, y + 2, xdest, ydest);
	this->_cubes[3] = new Cube(CYAN, x, y + 3, xdest, ydest);
	this->_pivotX = x+0; this->_pivotY = y+1;
}
void Piece::_setRed(char x,char y, int xdest, int ydest)
{
	this->_cubes[0] = new Cube(RED, x, y, xdest, ydest);
	this->_cubes[1] = new Cube(RED, x+1, y, xdest, ydest);
	this->_cubes[2] = new Cube(RED, x+1, y+1, xdest, ydest);
	this->_cubes[3] = new Cube(RED, x+2, y+1, xdest, ydest);
	this->_pivotX = x + 1; this->_pivotY = y + 0;
}
void Piece::_setOrange(char x, char y, int xdest, int ydest)
{
	this->_cubes[0] = new Cube(ORANGE, x, y+1, xdest, ydest);
	this->_cubes[1] = new Cube(ORANGE, x+1, y + 1, xdest, ydest);
	this->_cubes[2] = new Cube(ORANGE, x + 2, y, xdest, ydest);
	this->_cubes[3] = new Cube(ORANGE, x + 2, y+1, xdest, ydest);
	this->_pivotX = x + 1; this->_pivotY = y + 1;
}

void Piece::draw(SDL_Renderer*ren,Sprite* sprite)
{
	this->_cubes[0]->draw(ren, sprite);
	this->_cubes[1]->draw(ren, sprite);
	this->_cubes[2]->draw(ren, sprite);
	this->_cubes[3]->draw(ren, sprite);
}
void Piece::_rotate()
{
	if (this->color != YELLOW)
	{
		for (char i = 0; i < 4; i++)
		{
			char vrx = this->_cubes[i]->getX() - _pivotX;
			char vry = this->_cubes[i]->getY() - _pivotY;

			char vtx = (0 * vrx) + (-1 * vry);
			char vty = (1 * vrx) + (0 * vry);

			this->_cubes[i]->setX(_pivotX + vtx);
			this->_cubes[i]->setY(_pivotY + vty);

			this->_cubes[i]->update();
		}
	}

}

void Piece::rotateLeft()
{
	this->_rotate();
	this->_rotate();
	this->_rotate();

	if (this->_borderLeft() || _borderRight())
	{
		this->rotateRight();
	}
	if (this->falled())
	{
		this->rotateRight();
		this->down();
	}
}

void Piece::rotateRight()
{
	this->_rotate();
	if (this->_borderLeft() ||this->_borderRight())
	{
		this->rotateLeft();
	}
	if (this->falled())
	{
		this->rotateLeft();
		this->down();
	}
}

bool Piece::_borderLeft()
{
	if (this->_cubes[0]->borderLeft() || this->_cubes[1]->borderLeft() || this->_cubes[2]->borderLeft() || this->_cubes[3]->borderLeft())
	{
		return true;
	}
	return false;
}
bool Piece::_borderRight()
{
	if (this->_cubes[0]->borderRight() || this->_cubes[1]->borderRight() || this->_cubes[2]->borderRight() || this->_cubes[3]->borderRight())
	{
		return true;
	}
	return false;
}

void Piece::up()
{
	this->_cubes[0]->up();
	this->_cubes[2]->up();
	this->_cubes[1]->up();
	this->_cubes[3]->up();
	this->_pivotY--;
}
void Piece::down()
{
	this->_cubes[0]->down();
	this->_cubes[1]->down();
	this->_cubes[2]->down();
	this->_cubes[3]->down();
	this->_pivotY++;
}
void Piece::left()
{
	this->_cubes[0]->left();
	this->_cubes[1]->left();
	this->_cubes[2]->left();
	this->_cubes[3]->left();
	this->_pivotX--;
	if (this->_cubes[0]->borderLeft() || this->_cubes[1]->borderLeft() || this->_cubes[2]->borderLeft() || this->_cubes[3]->borderLeft())
	{
		this->right();
	}
}
void Piece::right()
{
	this->_cubes[0]->right();
	this->_cubes[1]->right();
	this->_cubes[2]->right();
	this->_cubes[3]->right();
	this->_pivotX++;
	if (this->_cubes[0]->borderRight() || this->_cubes[1]->borderRight() || this->_cubes[2]->borderRight() || this->_cubes[3]->borderRight())
	{
		this->left();
	}
}

bool Piece::falled()
{
	if (this->_cubes[0]->falled() || this->_cubes[1]->falled() || this->_cubes[2]->falled() || this->_cubes[3]->falled())
	{
		this->up();
		return true;
	}
	return false;
}
bool Piece::collision(CubeStruct cube)
{
	if (this->_cubes[0]->collision(cube) || this->_cubes[1]->collision(cube)|| this->_cubes[2]->collision(cube)|| this->_cubes[3]->collision(cube))
	{
		return true;
	}
	return false;
}

CubeArray Piece::getCubes()
{
	CubeArray temp;
	temp.cubes[0] = new Cube(this->_cubes[0]);
	temp.cubes[1] = new Cube(this->_cubes[1]);
	temp.cubes[2] = new Cube(this->_cubes[2]);
	temp.cubes[3] = new Cube(this->_cubes[3]);
	return temp;
}

bool Piece::upper()
{
	if (this->_cubes[0]->upper() || this->_cubes[1]->upper() || this->_cubes[2]->upper() || this->_cubes[3]->upper())
	{
		return true;
	}
	return false;
}

Piece::~Piece()
{
	this->_cubes[0]->~Cube();
	this->_cubes[1]->~Cube();
	this->_cubes[2]->~Cube();
	this->_cubes[3]->~Cube();
}
