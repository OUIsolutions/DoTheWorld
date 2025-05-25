#include "doTheWorldOne.c"

int main(){
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    free(part->last_modification_in_str);
    part->last_modification_in_str = NULL;
    part->last_modification_time = 0;
    DtwTreePart_represent(part);
    DtwTreePart_free(part);
}