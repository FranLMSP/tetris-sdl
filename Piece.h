#pragma once
#include "Cube.h"

struct CubeArray
{
	Cube *cubes[4];
};

class Piece
{
public:
	Piece(Color color,char x,char y,int xdest,int ydest);
	Piece();
	~Piece();

	void draw(SDL_Renderer*ren,Sprite* sprite);

	void up();
	void down();
	void left();
	void right();

	bool falled();
	bool upper();
	bool collision(CubeStruct cube);

	void rotateLeft();
	void rotateRight();

	CubeArray getCubes();
private:
	Cube* _cubes[4];

	void _setBlue(char x, char y, int xdest, int ydest);
	void _setYellow(char x, char y, int xdest, int ydest);
	void _setMagenta(char x,char y, int xdest, int ydest);
	void _setGreen(char x,char y, int xdest, int ydest);
	void _setCyan(char x,char y, int xdest, int ydest);
	void _setRed(char x,char y, int xdest, int ydest);
	void _setOrange(char x,char y, int xdest, int ydest);

	void _rotate();

	Color color;
	unsigned char _pivotX, _pivotY;
	bool _borderLeft();
	bool _borderRight();
};

