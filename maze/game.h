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

using namespace std;

//game.cpp
void gameLoop(SDL_Renderer* rend, int screenWidth, int screenHeight);

//maze.cpp
class Maze{
    vector<int> getLegalMoves(int x, int y);
    //
    public:
        Maze(SDL_Point dims, SDL_Point start, SDL_Point end);
        //
        SDL_Point dims;//I'll need to use a malloc if I want flexible dims :(
        SDL_Point start;
        SDL_Point end;
        //
        Matrix<unsigned short> walls;//1d dynamic array which simulates a 3d array: x,y,2 walls (0 = right, 1 = bottom)
};

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