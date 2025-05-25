#include "doTheWorldOne.c"

int main(){
    DtwPath *path = newDtwPath("a/b/c/d.txt");
    char *name = DtwPath_get_full_name(path);
    char *extension = DtwPath_get_extension(path);
    char *dir = DtwPath_get_dir(path);
    char *full_path = DtwPath_get_path(path);
    printf("name : %s\n",name);
    printf("extension : %s\n",extension);
    printf("dir : %s\n",dir);
    printf("full_path : %s\n",full_path);
    DtwPath_free(path);
}