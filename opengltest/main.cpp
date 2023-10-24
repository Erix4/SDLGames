// Handle startup, exit, and window management

/*
Notes for myself:

Make sure to add new files to the OBJS in the Makefile
You shouldn't need to touch this file, look in game.cpp and beyond instead

*/


//Using SDL and standard IO
#include "game.h"
#include <list>
#include <ctime>
#include <assert.h>

//redfine types for ease of typing
typedef uint32_t u32;

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
    //Set OpenGL forward compatibility (>= 3.2)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    //
    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL );
    if( window == NULL ){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }
    //
    SDL_GLContext context = SDL_GL_CreateContext(window);
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
    //srand ( time(NULL) );
    //
    //gameLoop(rend, SCREEN_WIDTH, SCREEN_HEIGHT);
    //
    SDL_Event windowEvent;
    while (true){
        if (SDL_PollEvent(&windowEvent)){//check for new events
            if (windowEvent.type == SDL_QUIT) break;//if event is quit, then quit
            //
            if (windowEvent.type == SDL_KEYUP &&
            windowEvent.key.keysym.sym == SDLK_ESCAPE) break;//if escape key lifted, quit
        }
        //
        SDL_GL_SwapWindow(window);
    }
    //
    //Destroy SDL Context
    SDL_GL_DeleteContext(context);
    //
    //Destroy window
    SDL_DestroyWindow( window );
    //
    //Quit SDL subsystems
    SDL_Quit();
    //
    return 0;
}
