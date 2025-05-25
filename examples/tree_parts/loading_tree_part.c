#include "doTheWorldOne.c"

int main(){
    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    DtwTreePart_represent(part);
    DtwTreePart_free(part);
}