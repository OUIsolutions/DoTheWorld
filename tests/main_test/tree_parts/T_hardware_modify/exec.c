#include "../../../doTheWorld_test.h"


int main(){

    DtwTreePart *part = newDtwTreePartLoading("exemple_folder/a.txt");

    DtwPath *path = part->path;

    path->set_extension(path,"md");

    part->hardware_modify(part,DTW_EXECUTE_NOW);
    part->hardware_commit(part);
    part->free(part);

}