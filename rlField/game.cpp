//handle game initialization and loop


//using SDL and Standard io
#include <list>
#include "game.h"

void render(SDL_Renderer* rend, SDL_Rect creature){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);//clear screen
    SDL_RenderClear(rend);
    //
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);//set render color to red
    //
    SDL_RenderFillRect(rend, &creature);
    SDL_RenderPresent(rend);
}

void createField(int field[CELL_ROWS][CELL_COLS]){
    for(int i = 0; i < CELL_ROWS; i++){
        for(int j = 0; j < CELL_COLS; j++){
            field[i][j] = 0;
        }
    }
}

void gameLoop(SDL_Renderer* rend, int screenWidth, int screenHeight){
    int field[CELL_ROWS][CELL_COLS];//create field
    createField(field);
    //
    //
    //Creature cre = createCreature(0, 0);//initiliaze new creature at 0, 0
    Creature cre = createCreature(rand() % CELL_COLS, rand() % CELL_ROWS);//initiliaze new creature in random location
    //
    //Hack to get window to stay up
    SDL_Event e;
    int quit = 0;
    while( quit == 0 ){
        //
        while( SDL_PollEvent( &e ) ){
            switch (e.type){
                case SDL_QUIT:
                    printf("quit registered\n");
                    quit = 1;
                    break;
                default:
                    break;
            }
        }
        //
        render(rend, cre.rect);
    }
}