
#include "src/one.c"
DtwNamespace dtw;
int main(){
    dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartEmpty("tests/target/a.txt");
    dtw.tree.part.set_string_content(part,"my mensage2");
    dtw.tree.part.hardware_write(part,DTW_SET_AS_ACTION);
    dtw.tree.part.hardware_commit(part);
    dtw.tree.part.free(part);
}