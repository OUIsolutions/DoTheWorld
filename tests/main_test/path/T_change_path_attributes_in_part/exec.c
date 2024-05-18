
#include "../../../doTheWorld_test.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();
    DtwTreePart * part =  dtw.tree.part.newPartLoading("test/target/blob.png");
    DtwPath * path = part->path;
    dtw.path.set_name(path,"new_blob");
    dtw.tree.part.hardware_modify(part,DTW_SET_AS_ACTION);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);


}