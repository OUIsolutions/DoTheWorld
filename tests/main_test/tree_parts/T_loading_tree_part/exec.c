

#include "../../../doTheWorld_test.h"

int main(){

    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    part->represent(part);
    part->free(part);
}