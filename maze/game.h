#ifndef GAME_HEADER
#define GAME_HEADER

//Screen dimension constants
int const SCREEN_WIDTH = 750;//640;
int const SCREEN_HEIGHT = 550;//480;

//game constants
int const CELL_SIZE = 2;

int const PLAYER_SIZE = CELL_SIZE * 3 / 4;
int const PLAYER_SPEED = 200;

int const CELL_COLS = SCREEN_WIDTH / CELL_SIZE;
int const CELL_ROWS = SCREEN_HEIGHT / CELL_SIZE;
int const CELL_NUM = CELL_COLS * CELL_ROWS;

#include <stdio.h>
#include "SDL2/SDL.h"
#include <vector>

//game.cpp
void gameLoop(SDL_Renderer* rend, int screenWidth, int screenHeight);


//utils.cpp
#include "utils.cpp"

//maze.cpp
//template <class T> class Matrix;
class Maze{
    std::vector<int> getLegalMoves(int x, int y);
    SDL_Point moveToCoords(int move);
    //
    public:
        //Maze(SDL_Point dims, SDL_Point start, SDL_Point end);
        Maze(SDL_Point, SDL_Point);
        //
        SDL_Point dims;//I'll need to use a malloc if I want flexible dims :(
        SDL_Point start;
        SDL_Point end;
        //
        Matrix<short> walls;//1d dynamic array which simulates a 3d array: x,y,2 walls (0 = none, 1 = right, 2 = bottom, 3 = both, 4 = unset)
};

#endif