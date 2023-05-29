//objects which can be rendered


#include "game.h"

void RenderOb::setPos(int nx, int ny){
    x = nx;
    y = ny;
    rect.x = nx;
    rect.y = ny;
}

RenderOb createOb(int x, int y){
    RenderOb newOb;
    //
    newOb.x = x;
    newOb.y = y;
    newOb.rect = {x, y, CRE_SIZE * CELL_SIZE, CRE_SIZE * CELL_SIZE};
    //
    return newOb;
}