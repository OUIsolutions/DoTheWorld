#define DTW_DEBUG_TIME
#include "src/one.c"


int main(){
    DtwNamespace dtw = newDtwNamespace();
    DtwTreePart *part = dtw.tree.part.newPartLoading("tests/target/a.txt");
    part->last_modification_in_str = NULL;
    part->last_modification_time = 0;
    dtw.tree.part.represent(part);
    dtw.tree.part.free(part);
}