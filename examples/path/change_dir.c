
#include "doTheWorldOne.c"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = dtw.path.newPath("a/b/c/d.txt");
    dtw.path.set_dir(path,"test");
    dtw.path.represent(path);
    dtw.path.free(path);


}
