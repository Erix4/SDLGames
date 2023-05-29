//control creature's movements


#include "game.h"

void Creature::update(){
    //
}

Creature createCreature(int x, int y){
    Creature newCreature;
    //
    newCreature.x = x;
    newCreature.y = y;
    newCreature.rect = {x, y, CRE_SIZE * CELL_SIZE, CRE_SIZE * CELL_SIZE};
    //
    return newCreature;
}