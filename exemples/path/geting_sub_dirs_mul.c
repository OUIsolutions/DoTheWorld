
#include "doTheWorld.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = dtw.path.newPath(bd.txt");
    char *dir = dtw.path.get_sub_dirs_from_index(path,1,2);
    printf("dir:%s\n",dir);
    dtw.path.free(path);


}