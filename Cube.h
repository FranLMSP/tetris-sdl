#pragma once
#include <SDL2/SDL.h>
#include "Sprite.h"

enum Color{BLUE,YELLOW,MAGENTA,GREEN,CYAN,RED,ORANGE};
enum Type {SOLID,TRANSPARENT,NONE};

struct CubeStruct {
	SDL_Rect source, dest;
	char x, y;
	Color color;
	Type type;
};

class Cube
{
public:
	Cube(Color color, char x, char y, int xdest, int sourcedest);
	Cube();
	Cube(Cube*clone);
	~Cube();

	CubeStruct getCube();

	char getX();
	char getY();
	void setX(char x);
	void setY(char y);

	SDL_Rect getDest();

	SDL_Rect getSource();

	Type getType();

	void draw(SDL_Renderer*ren, Sprite* sprite);

	void up();
	void down();
	void left();
	void right();

	void update();

	bool collision(CubeStruct cube);
	bool upper();
	bool falled();
	bool borderLeft();
	bool borderRight();

private:
	char _xdest,_ydest;

	CubeStruct _cube;

	void _setDest(char xdest,char ydest);


	void _setSource(SDL_Rect source);

	void _setColor(Color color);
	void _setType(Type type);
};
