#pragma once

#include <string>
#include "Sprite.h"
#include "Piece.h"

class InGame
{
public:
	InGame();
	InGame(SDL_Renderer*ren,int destx,int desty);
	~InGame();

	void setX(int val);
	void setY(int val);
	int getX();
	int getY();

	void initArray();

	void update();
	void draw(SDL_Renderer*ren);

	void keyLeft();
	void keyRight();
	void keyRotateR();
	void keyRotateL();
	void heldDown();
	void releasedDown();
private:
	unsigned char _frameCounter;
	void _timerStart();
	void _frameCount();
	unsigned char _frameStop;

	void drawPiece(SDL_Renderer*ren);
	void drawArray(SDL_Renderer*ren);
	void drawBorder(SDL_Renderer*ren);

	void createPiece();
	void putPiece();
	void _clearLines();
	void _fallLines();
	void _drawArray();


	Sprite* _squares, *_border;
	SDL_Rect _borderSource, _borderDest;
	SDL_Rect _backgroundSource, _backgroundDest;

	Piece* _currentPiece;
	CubeStruct _cubeArray[10][20];

	bool _collision();

	int _x, _y;
	


};

