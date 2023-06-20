//
// Created by jurandi on 20-06-2023.
//
#include "../../doTheWorld_test.h"


int main(){

    struct DtwTreePart *part = newDtwTreePart(
            "test.txt",
            DTW_LOAD_CONTENT,
            DTW_LOAD_METADATA
    );

    struct DtwPath *path = part->path;

    char *name = path->get_full_name(path);
    char *extension = path->get_extension(path);
    char *dir = path->get_dir(path);
    char *full_path = path->get_path(path);
    printf("name : %s\n",name);
    printf("extension : %s\n",extension);
    printf("dir : %s\n",dir);
    printf("full_path : %s\n",full_path);


    free(name);
    free(extension);
    free(dir);
    free(full_path);
    part->free(part);
}