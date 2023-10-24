//handle game initialization and loop


//using list
#include <list>
#include "game.h"

void render(SDL_Renderer* rend){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);//clear screen(backbuffer)
    SDL_RenderClear(rend);
    //
    SDL_RenderPresent(rend);//load backbuffer onto screen
}

SDL_Point collisionDetection(int field[CELL_ROWS][CELL_COLS], SDL_Point playerPos, SDL_Point playerVel, double delta){//some bouncing happens when hitting corner
    int cellX = playerPos.x / CELL_SIZE;//cell which top left corner of player is in
    int cellY = playerPos.y / CELL_SIZE;
    //
    int sizeCellX = (playerPos.x + PLAYER_SIZE) / CELL_SIZE;//cell which bottom right corner of player is in
    int sizeCellY = (playerPos.y + PLAYER_SIZE) / CELL_SIZE;
    //
    SDL_Point newVel = {playerVel.x, playerVel.y};//initiliaze output as input
    //
    if(playerVel.x > 0 && playerPos.x + PLAYER_SIZE + (playerVel.x * delta) > (cellX + 1) * CELL_SIZE){//check for position breaching new cell
        if(field[cellY][cellX + 1] == 1 || field[sizeCellY][cellX + 1] == 1){//check that new cell is a wall
            newVel.x = ((cellX + 1) * CELL_SIZE - PLAYER_SIZE - playerPos.x - 1) / delta;//set movement to stop at wall
        }
    }else if(playerPos.x + (playerVel.x * delta) < (cellX) * CELL_SIZE){//same for left direction
        if(field[cellY][cellX - 1] == 1 || field[sizeCellY][cellX - 1] == 1){
            newVel.x = ((cellX) * CELL_SIZE - playerPos.x + 1) / delta;//give one pixel leeway to prevent future collisions
        }
    }
    //
    cellX = (playerPos.x + (newVel.x * delta)) / CELL_SIZE;//perform y checking based on approved new x position
    //
    if(playerVel.y > 0 && playerPos.y + PLAYER_SIZE + (playerVel.y * delta) > (cellY + 1) * CELL_SIZE){
        if(field[cellY + 1][cellX] == 1 || field[cellY + 1][sizeCellX] == 1){
            newVel.y = ((cellY + 1) * CELL_SIZE - PLAYER_SIZE - playerPos.y - 1) / delta;
        }
    }else if(playerPos.y + (playerVel.y * delta) < (cellY) * CELL_SIZE){
        if(field[cellY - 1][cellX] == 1 || field[cellY - 1][sizeCellX] == 1){
            newVel.y = ((cellY) * CELL_SIZE - playerPos.y + 1) / delta;
        }
    }
    //
    return newVel;
}

void gameLoop(SDL_Renderer* rend, int screenWidth, int screenHeight){
    printf("starting game loop\n");
    //
    Uint64 lastTime = SDL_GetTicks64();
    //
    //Hack to get window to stay up
    SDL_Event e;
    int quit = 0;
    while( quit == 0 ){
        double delta = ((double)(SDL_GetTicks64() - lastTime) / 1000);
        lastTime = SDL_GetTicks64();
        //
        double accelAmount = PLAYER_ACCEL * delta;
        //
        while( SDL_PollEvent( &e ) ){
            switch (e.type){
                case SDL_QUIT:
                    printf("quit registered\n");
                    quit = 1;
                    break;
                case SDL_KEYDOWN://key press registered
                    switch (e.key.keysym.scancode){
                        default:
                            //printf("other key pressed\n");
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        //
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        //
        render(rend);
    }
}