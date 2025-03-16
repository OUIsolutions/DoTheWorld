
#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();
    DtwPath *path = dtw.path.newPath("a/b/c/d.txt");
    char *name = dtw.path.get_full_name(path);
    char *extension = dtw.path.get_extension(path);
    char *dir = dtw.path.get_dir(path);
    char *full_path = dtw.path.get_path(path);
    printf("name : %s\n",name);
    printf("extension : %s\n",extension);
    printf("dir : %s\n",dir);
    printf("full_path : %s\n",full_path);
    dtw.path.free(path);


}
