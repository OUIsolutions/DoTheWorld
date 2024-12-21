
#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = dtw.path.newPath(bd.txt");
    dtw.path.insert_dir_at_index(path,0,"test");
    dtw.path.represent(path);
    dtw.path.free(path);

}