
#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = dtw.path.newPath("a/b/c/d.txt");
    dtw.path.set_name(path,"test");
    dtw.path.set_extension(path,"md");
    dtw.path.represent(path);
    dtw.path.free(path);


}