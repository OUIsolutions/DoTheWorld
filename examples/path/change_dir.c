#include "doTheWorldOne.c"

int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = newDtwPath("a/b/c/d.txt");
    DtwPath_set_dir(path,"test");
    DtwPath_represent(path);
    DtwPath_free(path);


}