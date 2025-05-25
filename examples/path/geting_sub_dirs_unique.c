#include "doTheWorldOne.c"

int main(){
    DtwPath * path = newDtwPath("a/b/c/d.txt");
    char *dir = DtwPath_get_sub_dirs_from_index(path, 0, 0);
    printf("dir:%s\n", dir);
    DtwPath_free(path);
}