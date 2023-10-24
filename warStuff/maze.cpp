//maze object to worry about where walls area

#include "game.h"
#include <stack>

Maze::Maze(SDL_Point dims, SDL_Point start) : walls(dims.x, dims.y, 4){
    this->dims = dims;
    this->start = start;
    printf("entered constructor\n");
    //
    std::stack<int> movePath;
    //
    int curX = 0, curY = 0, cellsVisited = 1, move = 0;
    //
    printf("beginning maze generation\n");
    while(cellsVisited < dims.x * dims.y){
        std::vector<int> moves = this->getLegalMoves(curX, curY);
        //
        /*printf("%d, (%d, %d)\n", cellsVisited, curX, curY);
        for(int i = 0; i < dims.y; i++){
            for(int j = 0; j < dims.x; j++){
                printf("%d", walls.get(j, i));
            }
            printf("\n");
        }
        printf("moves: %d\n", moves.size());*/
        //
        SDL_Point moveCoords;
        if(moves.size() == 0){//dead end, return go back a step
            move = movePath.top();
            movePath.pop();
            moveCoords = moveToCoords(move);
            //
            if(walls.get(curX, curY) == 4){
                walls.set(curX, curY, 3);
            }
            //
            curX -= moveCoords.x;
            curY -= moveCoords.y;
        }else{
            int move = moves[rand() % moves.size()];//pick a random move
            moveCoords = moveToCoords(move);
            //printf("move chosen: %d, (%d, %d)\n", move, moveCoords.x, moveCoords.y);
            //
            movePath.push(move);
            //
            int prevX = curX;
            int prevY = curY;
            //
            curX += moveCoords.x;
            curY += moveCoords.y;
            cellsVisited++;
            //
            if(move < 2){
                walls.set(curX, curY, move+1);//up0->1, left1->2
                if(walls.get(prevX, prevY) == 4){//the walls has been set
                    walls.set(prevX, prevY, 3);//the current cell has not been visited and should be filled in to show visitation
                    //the above only happens when the path enters from the left and move goes upward
                }
            }else{
                /*
                There are two scenario where a wall is already set:
                    1. the previous move was up or left and entered this cell (1 or 2 only)
                    2. the program is backtracking from a deadend and this cell has already been visited
                If the new move is up or left, no change should be made to the current cell's wall state.
                If the move is down or right, remove the wall in the way (2,1->0, 3->2,1), cur+m-4
                */
                if(walls.get(prevX, prevY) < 4){//the walls has been set
                    walls.set(prevX, prevY, walls.get(prevX, prevY) + move - 4);
                }else{//wall has not been set
                    walls.set(prevX, prevY, move - 1);
                }
            }
        }
    }
    //
    if(walls.get(curX, curY) == 4){
        walls.set(curX, curY, 3);
    }
    //
    end = moveToCoords(move);//set end as last visited cell
}

std::vector<int> Maze::getLegalMoves(int x, int y){
    std::vector<int> moves;
    moves.reserve(4);//give the vector a capacity of 4 to avoid unnecessary reallocation
    //
    if(y > 0 && walls.get(x, y-1) == 4){
        moves.push_back(0);//move up
    }
    if(x > 0 && walls.get(x-1, y) == 4){
        moves.push_back(1);//move left
    }
    if(y < this->dims.y - 1 && walls.get(x, y+1) == 4){
        moves.push_back(2);//move down
    }
    if(x < this->dims.x - 1 && walls.get(x+1, y) == 4){
        moves.push_back(3);//move right
    }
    //
    return moves;
}

SDL_Point Maze::moveToCoords(int move){
    if(move % 2 == 1){
        return {move - 2, 0};
    }else{
        return {0, move - 1};
    }
}