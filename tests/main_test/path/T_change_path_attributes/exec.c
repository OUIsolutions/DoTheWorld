
#include "../../../doTheWorld_test.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/sub_folder/a.txt");

    DtwPath *path = part->path;

    dtw.path.set_dir(path,"a/b");
    dtw.path.set_name(path,"test2");
    dtw.path.set_extension(path,"md");
    dtw.path.represent(path);
    dtw.tree.part.hardware_modify(part,DTW_SET_AS_ACTION);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);

}