#include "doTheWorldOne.c"

int main(){
    DtwPath * path = newDtwPath("a/b/c/d.txt");
    DtwPath_replace_dirs(path, "b/c", "test");
    DtwPath_represent(path);
    DtwPath_free(path);
}
