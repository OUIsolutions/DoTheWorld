#include "doTheWorldOne.c"

int main(){
    DtwPath * path = newDtwPath("a/b/c/d.txt");
    DtwPath_set_name(path, "test");
    DtwPath_set_extension(path, "md");
    DtwPath_represent(path);
    DtwPath_free(path);
    return 0;
}