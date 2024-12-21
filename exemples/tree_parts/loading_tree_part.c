

#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("testarga.txt");
    dtw.tree.part.represent(part);
    dtw.tree.part.free(part);
}