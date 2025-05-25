#include "doTheWorldOne.c"

int main(){
    DtwTreePart * part = newDtwTreePartLoading("tests/target/blob.png");
    DtwPath_set_name(part->path, "new_blob");
    DtwTreePart_hardware_modify(part, DTW_SET_AS_ACTION);
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);
}