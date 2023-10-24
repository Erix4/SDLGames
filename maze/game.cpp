//handle game initialization and loop


//using list
#include <list>
#include "game.h"

void render(SDL_Renderer* rend, int field[CELL_ROWS][CELL_COLS], SDL_Point playerPos){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);//clear screen(backbuffer)
    SDL_RenderClear(rend);
    //
    for(int i = 0; i < CELL_ROWS; i++){
        for(int j = 0; j < CELL_COLS; j++){
            if(field[i][j] == 1){//check field status
                SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);//set render color to black
            }else{
                SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);//set render color to white
            }
            //
            SDL_Rect curRect = {j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_RenderFillRect(rend, &curRect);
        }
        //
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
        SDL_Rect curRect = {playerPos.x, playerPos.y, PLAYER_SIZE, PLAYER_SIZE};
        SDL_RenderFillRect(rend, &curRect);
    }
    //
    SDL_RenderPresent(rend);//load backbuffer onto screen
}

void createField(int field[CELL_ROWS][CELL_COLS], Maze maze){//TODO: use maze to pick cells to fill in
    for(int i = 0; i < CELL_ROWS; i++){
        for(int j = 0; j < CELL_COLS; j++){
            if(i == 0 || j == 0){
                field[i][j] = 1;
                continue;
            }
            if((i % 2 == 0 && j % 2 == 0) ||//maze corner
                (i % 2 == 1 && j % 2 == 0 && maze.walls.get((j - 1) / 2, (i - 1) / 2) % 2 == 1) ||
                (i % 2 == 0 && j % 2 == 1 && (maze.walls.get((j - 1) / 2, (i - 1) / 2) == 2 || maze.walls.get((j - 1) / 2, (i - 1) / 2) == 3))){
                field[i][j] = 1;
            }else{
                field[i][j] = 0;
            }
        }
    }
    //
    //field[1][1] = 1;
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
    int field[CELL_ROWS][CELL_COLS];//create field
    Maze maze(SDL_Point{(CELL_COLS - 1) / 2, (CELL_ROWS - 1) / 2}, SDL_Point{0, 0});
    createField(field, maze);
    //
    SDL_Point playerPos = {CELL_SIZE, CELL_SIZE};// position always describes top left corner
    SDL_Point playerVel = {0, 0};
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
        double xAccel = accelAmount * (abs(playerVel.x) / 50 + 1);
        //
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_LEFT]){
            if(playerVel.x - xAccel > -PLAYER_SPEED){
                playerVel.x -= xAccel;
            }else{
                playerVel.x = -PLAYER_SPEED;
            }
        }else if(keystates[SDL_SCANCODE_RIGHT]){
            if(playerVel.x + xAccel < PLAYER_SPEED){
                playerVel.x += xAccel;
            }else{
                playerVel.x = PLAYER_SPEED;
            }
        }else{
            playerVel.x -= abs(playerVel.x) > accelAmount ? sgn<int>(playerVel.x) * accelAmount : playerVel.x;
        }
        //
        double yAccel = accelAmount * (abs(playerVel.y) / 50 + 1);
        //
        if(keystates[SDL_SCANCODE_UP]){
            if(playerVel.y - yAccel > -PLAYER_SPEED){
                playerVel.y -= yAccel;
            }else{
                playerVel.y = -PLAYER_SPEED;
            }
        }else if(keystates[SDL_SCANCODE_DOWN]){
            if(playerVel.y + yAccel < PLAYER_SPEED){
                playerVel.y += yAccel;
            }else{
                playerVel.y = PLAYER_SPEED;
            }
        }else{
            playerVel.y -= abs(playerVel.y) > accelAmount ? sgn<int>(playerVel.y) * accelAmount : playerVel.y;
        }
        //
        playerVel = collisionDetection(field, playerPos, playerVel, delta);
        //
        playerPos.x += playerVel.x * delta;
        playerPos.y += playerVel.y * delta;
        //
        render(rend, field, playerPos);
    }
}