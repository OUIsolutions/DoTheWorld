

#include "../../../doTheWorld_test.h"



int main(){

    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    part->hardware_remove(part,DTW_EXECUTE_NOW);
    part->hardware_commit(part);
    part->free(part);

}