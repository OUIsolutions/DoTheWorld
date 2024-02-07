#include "src/one.h"



int main(int argc, char *argv[]){
    DtwLocker *t = newDtwLocker();
    DtwLocker_lock(t,"a.txt");

}