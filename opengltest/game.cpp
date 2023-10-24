//handle game initialization and loop


//using list
#include <list>
#include "game.h"

void render(SDL_Renderer* rend){
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glClearColor(1.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    //SDL_GL_SwapWindow(rend);
    //
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);//clear screen(backbuffer)
    SDL_RenderClear(rend);
    //
    //
    //
    SDL_RenderPresent(rend);//load backbuffer onto screen
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
        render(rend);
    }
}