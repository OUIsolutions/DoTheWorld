
#include "doTheWorld.h"


int main(){

    DtwTreePart *part = newDtwTreePartLoading( "tests/target/a.txt");

    DtwPath *path = part->path;

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