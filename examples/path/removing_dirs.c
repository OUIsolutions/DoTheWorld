#include "doTheWorldOne.c"

int main(){
    DtwPath * path = newDtwPath("a/b/c/d.txt");
    DtwPath_remove_sub_dirs_at(path,"b/c");
    DtwPath_represent(path);
    DtwPath_free(path);
}