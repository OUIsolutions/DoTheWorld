
#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();
    DtwTreePart * part =  dtw.tree.part.newPartLoading("tests/target/blob.png");
    dtw.path.set_name(part->path,"new_blob");
    dtw.tree.part.hardware_modify(part,DTW_SET_AS_ACTION);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);


}