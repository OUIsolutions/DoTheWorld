#include "../../doTheWorld_test.h"


int main(){

    struct DtwTreePart *part = newDtwTreePart(
            "exemple_folder/a.txt",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA
    );

    struct DtwPath *path = part->path;

    path->set_extension(path,"md");

    part->hardware_modify(part,DTW_EXECUTE_NOW);
    part->hardware_commit(part);
    part->free(part);

}