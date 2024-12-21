
#include "../../../../release/doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = dtw.path.newPath("a/b/c/d.txt");
    dtw.path.insert_dir_at_index(path,0,"test");
    dtw.path.represent(path);
    dtw.path.free(path);

}
