#include "doTheWorld/doTheWorldMain.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

    DtwLocker *t = dtw.locker.newLocker();
    dtw.locker.lock(t,"a.txt");
    sleep(10);
    dtw.locker.free(t);
    
    
}