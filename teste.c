

#include "src/one.c"


int main(){
    DtwNamespace dtw = newDtwNamespace();

    DtwPath * path = dtw.path.newPath("a/b/c/d.txt");
    dtw.path.remove_sub_dirs_at(path,"b/c");
    dtw.path.represent(path);
    dtw.path.free(path);

}