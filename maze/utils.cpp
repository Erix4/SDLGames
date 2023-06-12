//#include "game.h"
#include <stdio.h>

template <typename T> class Matrix{
    T *list;
    int width;
    int height;
    //
    public:
        Matrix(int width, int height){
            this->width = width;
            this->height = height;
            //
            list = new T[width * height];
        }
        //
        Matrix(int width, int height, T fill){
            this->width = width;
            this->height = height;
            //
            list = new T[width * height];
            //
            for(int i = 0; i < width * height; i++){
                list[i] = fill;
            }
        }
        //
        ~Matrix(){
            delete[] list;
        }
        //
        T get(int x, int y){
            return list[y * width + x];
        }
        //
        void set(int x, int y, T v){
            list[y * width + x] = v;
        }
};