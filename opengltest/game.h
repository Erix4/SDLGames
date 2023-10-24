#ifndef GAME_HEADER
#define GAME_HEADER

//Screen dimension constants
int const SCREEN_WIDTH = 750;//640;
int const SCREEN_HEIGHT = 550;//480;

//game constants


#include <stdio.h>
#include "SDL2/SDL.h"
#include <vector>
#include <SDL_opengl.h>

//game.cpp
void gameLoop(SDL_Renderer* rend, int screenWidth, int screenHeight);





#endif