#include "doTheWorldOne.c"

int main(){
    DtwPath * path = newDtwPath("a/b/c/d.txt");
    DtwPath_insert_dir_at_index(path, 0, "test");
    DtwPath_represent(path);
    DtwPath_free(path);
}