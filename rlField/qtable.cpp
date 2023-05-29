#include "game.h"


class QTable{
    public:
        float get(int y, int x){
            return data[y][x];
        }
        void set(int y, int x, float v){
            data[y][x] = v;
        }
        float setAll(float v){
            for(int i = 0; i < CELL_NUM; i++){
                for(int j = 0; j < 4; j++){
                    data[i][j] = v;
                }
            }
        }
    private:
        float data[CELL_NUM][4];
};
