#include "InGame.h"
#include <time.h>
#include <stdlib.h>
InGame::InGame()
{
	srand(time(NULL));
}

InGame::InGame(SDL_Renderer*ren,int destx,int desty)
{
	srand(time(NULL));
	this->setX(destx);
	this->setY(desty);
	this->initArray();
	this->_timerStart();

	this->_squares = new Sprite(ren, NULL, { 0,0,0 }, "res/tetris.bmp");
	this->_border = new Sprite(ren, NULL, { 255,0,0 }, "res/box.bmp");
	
	this->_borderSource = {0,0,260,480};
	this->_borderDest = { 0,0,260,480 };
	this->_backgroundSource = { 260,0,220,440};
	this->_backgroundDest = { 20,20,220,440 };
	
	this->_frameStop = 30;
	this->createPiece();
	//this->_currentPiece->up();

}

void InGame::initArray()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			this->_cubeArray[i][j].type=NONE;
			this->_cubeArray[i][j].x = i;
			this->_cubeArray[i][j].y = j;
		}
	}
}

void InGame::_timerStart()
{
	this->_frameCounter = 0;
}
void InGame::_frameCount()
{
	this->_frameCounter++;
}

void InGame::update()
{
	if (this->_frameCounter >= this->_frameStop)
	{
		this->_timerStart();
		this->_currentPiece->down();

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (this->_currentPiece->collision(this->_cubeArray[i][j]))
				{
					this->_currentPiece->up();
					this->putPiece();

					this->createPiece();
				}

			}
		}

		if (this->_currentPiece->falled())
		{
			this->putPiece();			
		
			this->createPiece();
		}
	}

	this->_frameCount();
}

void InGame::putPiece()
{
	if (this->_currentPiece->upper())
	{
		this->initArray();
		this->createPiece();
	}
	else
	{
		CubeArray temp = this->_currentPiece->getCubes();
		this->_cubeArray[temp.cubes[0]->getX()][temp.cubes[0]->getY()] = temp.cubes[0]->getCube();
		this->_cubeArray[temp.cubes[1]->getX()][temp.cubes[1]->getY()] = temp.cubes[1]->getCube();
		this->_cubeArray[temp.cubes[2]->getX()][temp.cubes[2]->getY()] = temp.cubes[2]->getCube();
		this->_cubeArray[temp.cubes[3]->getX()][temp.cubes[3]->getY()] = temp.cubes[3]->getCube();

		this->_clearLines();
		this->_fallLines();
		this->_drawArray();
	}

}

void InGame::draw(SDL_Renderer*ren)
{
	this->drawBorder(ren);
	this->drawPiece(ren);
	this->drawArray(ren);
	
}
void InGame::drawBorder(SDL_Renderer*ren)
{
	this->_border->drawPiece(ren, this->_borderSource, this->_borderDest);
	this->_border->drawPiece(ren, this->_backgroundSource, this->_backgroundDest);
	
}
void InGame::drawArray(SDL_Renderer*ren)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			
			if (this->_cubeArray[i][j].type != NONE)
			{
				this->_squares->drawPiece(ren, this->_cubeArray[i][j].source, this->_cubeArray[i][j].dest);
			}
			
		}
	}
}
void InGame::drawPiece(SDL_Renderer*ren)
{
	this->_currentPiece->draw(ren, this->_squares);
}

void InGame::createPiece()
{
	char random = char(rand() % 7);
	Color color;
	switch (random)
	{
		case 0:color = YELLOW; break;
		case 1:color = CYAN; break;
		case 2:color = BLUE; break;
		case 3:color = MAGENTA; break;
		case 4:color = GREEN; break;
		case 5:color = RED; break;
		case 6:color = ORANGE; break;
		default:;
	}
	this->_currentPiece = new Piece(color, 4, 0, this->getX(), this->getY());
	random = char(rand() % 4);

	for (char i = 0; i < random; i++)
	{
		this->_currentPiece->rotateRight();
	}

}
void InGame::keyLeft()
{
	this->_currentPiece->left();
	if (this->_collision())
	{
		this->_currentPiece->right();
	}
}
void InGame::keyRight()
{
	this->_currentPiece->right();
	if (this->_collision())
	{
		this->_currentPiece->left();
	}
}
void InGame::keyRotateL()
{
	this->_currentPiece->rotateLeft();
	if (this->_collision())
	{
		this->_currentPiece->rotateRight();
	}
}
void InGame::keyRotateR()
{
	this->_currentPiece->rotateRight();
	if (this->_collision())
	{
		this->_currentPiece->rotateLeft();
	}
}
void InGame::heldDown()
{
	this->_frameStop = 5;
}
void InGame::releasedDown()
{
	this->_frameStop = 30;
}

void InGame::_clearLines()
{
	int cont = 0;
	int temp = 0;
	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (this->_cubeArray[i][j].type == SOLID)
			{
				cont++;
			}
		}
		if (cont == 10)
		{
			temp++;
			for (int k = 0; k < 10; k++)
			{
				this->_cubeArray[k][j].type = NONE;
			}
		}
		cont = 0;
	}
}

void InGame::_drawArray()
{
	for (char j = 0; j < 20; j++)
	{
		for (char i = 0; i < 10; i++)
		{
			if (this->_cubeArray[i][j].type == NONE)
			{
				std::cout << 0 << " ";
			}
			if (this->_cubeArray[i][j].type == SOLID)
			{
				std::cout << 1 << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void InGame::_fallLines()
{
	int cont = 0;
	for (int j = 1; j < 20; j++)
	{
		cont = 0;
		for (int i = 0; i < 10; i++)
		{
			if (this->_cubeArray[i][j].type == NONE)
			{
				cont++;
			}
		}

		if (cont >= 10)
		{
			for (int kj = j; kj >= 1; kj--)
			{
				for (int ki = 0; ki < 10; ki++)
				{
					this->_cubeArray[ki][kj] = this->_cubeArray[ki][kj - 1];
					this->_cubeArray[ki][kj].dest.y += 22;
					this->_cubeArray[ki][kj].y++;
				}
			}

		}
	}
}

bool InGame::_collision()
{
	for (char i = 0; i < 10; i++)
	{
		for (char j = 0; j < 20; j++)
		{
			if (this->_currentPiece->collision(this->_cubeArray[i][j]))
			{
				return true;
			}
		}
	}
	return false;
}

void InGame::setX(int val)
{
	this->_x = val;
}
int InGame::getX()
{
	return this->_x;
}

void InGame::setY(int val)
{
	this->_y = val;
}
int InGame::getY()
{
	return this->_y;
}

InGame::~InGame()
{
	this->_squares->~Sprite();
	this->_border->~Sprite();
	std::cout << "InGame destroyed" << std::endl;
}
