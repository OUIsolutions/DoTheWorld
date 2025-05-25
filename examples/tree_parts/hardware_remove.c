#include "doTheWorldOne.c"

int main(){
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    DtwTreePart_hardware_remove(part, DTW_EXECUTE_NOW);
    DtwTreePart_hardware_commit(part);
    DtwTreePart_free(part);

    return 0;
}