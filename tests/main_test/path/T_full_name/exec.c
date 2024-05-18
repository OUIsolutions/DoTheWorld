
#include "../../../doTheWorld_test.h"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = dtw.path.newPath("a/b/c/d.txt");
    dtw.path.set_full_name(path,"test.py");
    dtw.path.represent(path);
    dtw.path.free(path);


}