
#include "../../../../release/doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = dtw.path.newPath("a/b/c/d.txt");
    char *dir = dtw.path.get_sub_dirs_from_index(path,0,0);
    printf("dir:%s\n",dir);
    dtw.path.free(path);


}
