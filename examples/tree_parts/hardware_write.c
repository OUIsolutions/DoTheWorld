#include "doTheWorldOne.c"

int main(){
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    DtwPath_set_extension(part->path, "md");
    DtwTreePart_hardware_write(part, DTW_EXECUTE_NOW);
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);
}
