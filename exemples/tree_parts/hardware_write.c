
#include "doTheWorld.h"


int main(){

    DtwTreePart *part = newDtwTreePartLoading("tests/target/a.txt");

    DtwPath *path = part->path;

    path->set_extension(path,"md");

    part->hardware_write(part,DTW_EXECUTE_NOW);
    part->hardware_commit(part);
    part->free(part);

}