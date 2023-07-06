

#include "../../doTheWorld_test.h"

int main(){

    DtwTreePart *part = newDtwTreePartLoading("exemple_folder/a.txt");

    part->represent(part);
    part->free(part);
}