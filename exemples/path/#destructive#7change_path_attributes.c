
#include "../../doTheWorld_test.h"


int main(){

    DtwTreePart *part = newDtwTreePart(
            "exemple_folder/a.txt",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA
    );

    DtwPath *path = part->path;

    path->set_dir(path,"a/b");
    path->set_name(path,"test2");
    path->set_extension(path,"md");
    path->represent(path);
    part->hardware_modify(part,DTW_SET_AS_ACTION);
    part->hardware_commit(part);
    part->free(part);

}