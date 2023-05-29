//handle game initialization and loop


//using list
#include <list>
#include "game.h"

void render(SDL_Renderer* rend, int field[CELL_ROWS][CELL_COLS]){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);//clear screen(backbuffer)
    SDL_RenderClear(rend);
    //
    for(int i = 0; i < CELL_ROWS; i++){
        for(int j = 0; j < CELL_COLS; j++){
            if(field[i][j] == 0){//check field status
                SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);//set render color to black
            }else{
                SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);//set render color to white
            }
            //
            SDL_Rect curRect = {j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_RenderFillRect(rend, &curRect);
        }
    }
    //
    SDL_RenderPresent(rend);//load backbuffer onto screen
}

void createField(int field[CELL_ROWS][CELL_COLS]){
    for(int i = 0; i < CELL_ROWS; i++){
        for(int j = 0; j < CELL_COLS; j++){
            if(i % 2 == 0 && j % 2 == 0){//maze corner
                field[i][j] = 1;
            }else{
                field[i][j] = 0;
            }
        }
    }
    //
    //field[1][1] = 1;
}

void gameLoop(SDL_Renderer* rend, int screenWidth, int screenHeight){
    int field[CELL_ROWS][CELL_COLS];//create field
    createField(field);
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
        render(rend, field);
    }
}