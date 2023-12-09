
#include "../../../doTheWorld_test.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwTreePart *part = dtw.tree.part.newPartLoading( "tests/target/a.txt");

    DtwPath *path = part->path;

    char *name = dtw.path.get_full_name(path);
    char *extension = dtw.path.get_extension(path);
    char *dir = dtw.path.get_dir(path);
    char *full_path = dtw.path.get_path(path);
    printf("name : %s\n",name);
    printf("extension : %s\n",extension);
    printf("dir : %s\n",dir);
    printf("full_path : %s\n",full_path);

    dtw.tree.part.free(part);
}