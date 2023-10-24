//#include "game.h"
#include <stdio.h>
#include <vector>

template <typename T> class Vectrix{
    std::vector<T> list;
    int width;
    int height;
    //
    public:
        Vectrix(int width, int height) : list(){
            this->width = width;
            this->height = height;
            //
            list.reserve(width * height);
        }
        //
        Vectrix(int width, int height, T fill) : list(width * height, fill){//vector comes with a built in fill
            this->width = width;
            this->height = height;
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

template <typename T> class Quadtrix{
    Vectrix<T> topLeftMatrix;//replace the matricies with dynamically allocated version
    Vectrix<T> topRightMatrix;
    Vectrix<T> bottomLeftMatrix;
    Vectrix<T> bottomRightMatrix;
    //
    Quadtrix(int width, int height){//generate centered maze with no fill
        //
    }
    //
    Quadtrix(int width, int height, T fill){//generate centered maze with fill
        //
    }
    //
    T get(int x, int y){
        if(x < 0 && y < 0){
            return topLeftMatrix.get(-x - 1, -y - 1);
        }else if(x < 0){
            return bottomLeftMatrix.get(-x - 1, y);
        }else if(y < 0){
            return topRightMatrix.get(x, -y - 1);
        }else{
            return bottomRightMatrix.get(x, y);
        }
    }
    //
    void set(int x, int y, T v){
        if(x < 0 && y < 0){
            topLeftMatrix.set(-x - 1, -y - 1, v);
        }else if(x < 0){
            bottomLeftMatrix.set(-x - 1, y, v);
        }else if(y < 0){
            topRightMatrix.set(x, -y - 1, v);
        }else{
            bottomRightMatrix.set(x, y, v);
        }
    }
};

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}