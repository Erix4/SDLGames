#include "game.h"

template <typename T> Matrix<T>::Matrix(int width, int height){
    this->width = width;
    this->height = height;
    //
    T *list = new T[width * height];
}

template <typename T> Matrix<T>::Matrix(int width, int height, T fill){
    this->width = width;
    this->height = height;
    //
    T *list = new T[width * height];
    //
    for(int i = 0; i < width * height; i++){
        list[i] = fill;
    }
}

template <typename T> Matrix<T>::~Matrix(){
    delete[] list;
}

template <typename T> T Matrix<T>::get(int x, int y){
    return list[y * width + x];
}

template <typename T> void Matrix<T>::set(int x, int y, T v){
    list[y * width + x] = v;
}