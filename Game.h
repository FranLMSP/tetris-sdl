#pragma once
#include "Sprite.h"
#include "Input.h"
#include "Timer.h"
#include "InGame.h"

enum GameState{MENU,INGAME,PAUSE,QUIT};

class Game
{
    public:
        Game();
        ~Game();

        void init();
    private:
        GameState _gameState;

        void menuLoop();
        void gameLoop();
        void pauseLoop();

        void readInputs();

        void frameStart();
        void frameEnd();

        Graphics* _graphics;
        Input _input;
        Timer _timer;

        InGame* _inGame;

        Sprite* _sprite;

};
