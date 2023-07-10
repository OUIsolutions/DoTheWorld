

#include "../../../doTheWorld_test.h"

int main(){

    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");
    part->last_modification_time = 0;
    
    part->represent(part);
    part->free(part);
}