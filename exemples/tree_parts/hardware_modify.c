#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("testarga.txt");

    dtw.path.set_extension(part->path,"md");

    dtw.tree.part.hardware_modify(part,DTW_EXECUTE_NOW);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);

}