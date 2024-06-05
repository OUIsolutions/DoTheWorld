

#include "src/one.c"
int main(){
    DtwNamespace dtw = newDtwNamespace();


    DtwPath * path = dtw.path.newPath("a/b/c/d.txt");
    dtw.path.insert_dir_at_index(path,-1,"teste");
    printf("%s\n",dtw.path.get_path(path));
    //dtw.path.represent(path);
    dtw.path.free(path);
}