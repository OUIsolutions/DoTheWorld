

#include "../../../doTheWorld_test.h"



int main(){

    DtwTreePart *part = newDtwTreePartLoading("exemple_folder/a.txt");

    part->hardware_remove(part,DTW_EXECUTE_NOW);
    part->hardware_commit(part);
    part->free(part);

}