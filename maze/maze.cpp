//maze object to worry about where walls area

#include "game.h"

using namespace std;

Maze::Maze(SDL_Point dims, SDL_Point start, SDL_Point end){
    this->dims = dims;
    this->start = start;
    this->end = end;
    //
    walls = Matrix<unsigned short>(dims.x, dims.y, 4);//initialize 2d array (kinda) with all 4s
    //
    int curX = 0, curY = 0, cellsVisited = 0;
    //
    while(cellsVisited < dims.x * dims.y){
        vector<int> moves = getLegalMoves(curX, curY);
        //
        int move = moves[rand() % moves.size()];
    }
}

vector<int> Maze::getLegalMoves(int x, int y){
    vector<int> moves;
    moves.reserve(4);//give the vector a capacity of 4 to avoid unnecessary reallocation
    //
    if(y > 0 && walls.get(x, y-1) == 4){
        moves.push_back(0);
    }
    if(x > 0 && walls.get(x-1, y) == 4){
        moves.push_back(1);
    }
    if(y < dims.y - 1 && walls.get(x, y+1) == 4){
        moves.push_back(2);
    }
    if(x < dims.x - 1 && walls.get(x+1, y) == 4){
        moves.push_back(3);
    }
    //
    return moves;
}