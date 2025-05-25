#include "doTheWorldOne.c"

int main(){
    DtwPath * path = newDtwPath("a/b/c/d.txt");
    DtwPath_set_full_name(path, "test.py");
    DtwPath_represent(path);
    DtwPath_free(path);
}
