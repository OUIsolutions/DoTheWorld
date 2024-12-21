
#include "../../../../release/doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = dtw.path.newPath("a/b/c/d.txt");
    dtw.path.replace_dirs(path,"b/c","test");
    dtw.path.represent(path);
    dtw.path.free(path);

}
