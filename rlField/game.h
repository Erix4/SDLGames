//Screen dimension constants
int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;

//game constants
int const CRE_SIZE = 2;
int const CRE_SPEED = 20;

int const CELL_SIZE = 10;

int const CELL_COLS = SCREEN_WIDTH / CELL_SIZE;
int const CELL_ROWS = SCREEN_HEIGHT / CELL_SIZE;
int const CELL_NUM = CELL_COLS * CELL_ROWS;

#include <stdio.h>
//#include <SDL2/SDL.h>
#include "SDL2/SDL.h"

//game.cpp
void gameLoop(SDL_Renderer* rend, int screenWidth, int screenHeight);

//qtable.cpp
class QTable;

//renderOb.cpp
class RenderOb{
    public:
        int x;
        int y;
        SDL_Rect rect;
        //
        void setPos(int nx, int ny){};
};
RenderOb createOb(int x, int y);

//creature.cpp
class Creature : public RenderOb{
    public:
        void update();
};
Creature createCreature(int x, int y);