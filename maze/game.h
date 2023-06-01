#ifndef GAME_HEADER
#define GAME_HEADER

//Screen dimension constants
int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;

//game constants
int const CELL_SIZE = 10;

int const CELL_COLS = SCREEN_WIDTH / CELL_SIZE;
int const CELL_ROWS = SCREEN_HEIGHT / CELL_SIZE;
int const CELL_NUM = CELL_COLS * CELL_ROWS;

#include <stdio.h>
#include "SDL2/SDL.h"
#include <vector>

//game.cpp
void gameLoop(SDL_Renderer* rend, int screenWidth, int screenHeight);

//utils.cpp
template <typename T> class Matrix{
    T *list;
    int width;
    int height;
    //
    public:
        Matrix(int width, int height);
        Matrix(int width, int height, T fill);
        ~Matrix();
        T get(int x, int y);
        void set(int x, int y, T v);
};

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
        Matrix<short> walls;//1d dynamic array which simulates a 3d array: x,y,2 walls (0 = right, 1 = bottom)
};

#endif