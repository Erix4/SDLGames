#include "game.h"

template <typename T> int TestClass<T>::test(){
    return 2;
}

/*
template <typename T> TestClass<T>::TestClass(){
    //hi = 1;
}

template <typename T> TestClass<T>::TestClass(T number){
    hi = number;
}

template <typename T> TestClass<T>::~TestClass(){
    //nothing here
}*/

void LinkerHack (){//this code will not run but will force the code to compile
    TestClass<int> TestObj;
    TestObj.test();
}