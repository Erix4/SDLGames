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
        //SDL_RenderFillRect(rend, &curRect);
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

void gameLoop(SDL_Renderer* rend, int screenWidth, int screenHeight){
    printf("starting game loop\n");
    int field[CELL_ROWS][CELL_COLS];//create field
    Maze maze(SDL_Point{(CELL_COLS - 1) / 2, (CELL_ROWS - 1) / 2}, SDL_Point{0, 0});
    createField(field, maze);
    //
    SDL_Point playerPos = {15, 15};
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
        while( SDL_PollEvent( &e ) ){
            switch (e.type){
                case SDL_QUIT:
                    printf("quit registered\n");
                    quit = 1;
                    break;
                case SDL_KEYDOWN://key press registered
                    switch (e.key.keysym.scancode){
                        case SDL_SCANCODE_LEFT:
                            playerPos.x -= PLAYER_SPEED * delta;
                            break;
                        case SDL_SCANCODE_RIGHT:
                            playerPos.x += PLAYER_SPEED * delta;
                            break;
                        case SDL_SCANCODE_UP:
                            playerPos.y -= PLAYER_SPEED * delta;
                            break;
                        case SDL_SCANCODE_DOWN:
                            playerPos.y += PLAYER_SPEED * delta;
                            break;
                        default:
                            printf("other key pressed\n");
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        //
        render(rend, field, playerPos);
    }
}