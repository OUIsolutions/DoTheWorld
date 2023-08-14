

#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");
    part->last_modification_time = 0;
    
    dtw.tree.part.represent(part);
    dtw.tree.part.free(part);
}