//Using SDL and standard IO
#include <stdio.h>
#include <SDL2/SDL.h>
#include "bullet.cpp"
#include <list>

using namespace std;

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define PLAYER_SIZE 30
#define PLAYER_SPEED 200

//Player starting position
const int START_X = SCREEN_WIDTH / 2 - (PLAYER_SIZE / 2);
const int START_Y = SCREEN_HEIGHT - PLAYER_SIZE - 20;

void render(SDL_Renderer* rend, SDL_Rect player, list<bullet> bullets){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);//clear screen
    SDL_RenderClear(rend);
    //
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);//set render color to red
    //
    SDL_RenderFillRect(rend, &player);
    SDL_RenderPresent(rend);
    //
    list<bullet>::iterator it;
    for(it = bullets.begin(); it != bullets.end(); it++){
        SDL_RenderFillRect(rend, &(it->rect));
        SDL_RenderPresent(rend);
    }
}

int main(int argc, char* args[]){
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    //
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;
    //
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }
    //
    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }
    //
    //Create a renderer
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, render_flags);
    if (!rend){
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }
    //
    //Get window surface
    screenSurface = SDL_GetWindowSurface( window );
    //
    //Fill the surface white
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
    //
    //Update the surface
    SDL_UpdateWindowSurface( window );
    //
    list<bullet> bullets;
    //
    SDL_Rect player = {START_X, START_Y, PLAYER_SIZE, PLAYER_SIZE};
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
                        case SDL_SCANCODE_SPACE:
                            bullets.push_back(createBullet(player.x, player.y));
                            break;
                        case SDL_SCANCODE_LEFT:
                            player.x -= PLAYER_SPEED * delta;
                            break;
                        case SDL_SCANCODE_RIGHT:
                            player.x += PLAYER_SPEED * delta;
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
        list<bullet>::iterator it = bullets.begin();
        while(it != bullets.end()){
            if(it->deathTime < SDL_GetTicks64()){
                it = bullets.erase(it);//removes current element and iterates to the next one
            }else{
                updateBullet(&*it, delta);
                it++;
            }
        }
        //
        render(rend, player, bullets);
    }
    //
    //Destroy window
    SDL_DestroyWindow( window );
    //
    //Quit SDL subsystems
    SDL_Quit();
    //
    return 0;
}
