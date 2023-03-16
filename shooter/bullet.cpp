#include <SDL2/SDL.h>

#define BULLET_WIDTH 5
#define BULLET_HEIGHT 30
#define BLIMIT 50

#define BULLET_VEL 500

class bullet{
    public:
        SDL_Rect rect;
        Uint64 deathTime;
};

bullet createBullet(int x, int y){
    bullet newBullet;
    //
    newBullet.rect = {x, y, BULLET_WIDTH, BULLET_HEIGHT};
    newBullet.deathTime = SDL_GetTicks64() + 1000;//set death time
    //
    return newBullet;
}

void updateBullet(bullet* bullet, double delta){
    bullet->rect.y -= BULLET_VEL * delta;//update bullet position according to velocity and time passed
}