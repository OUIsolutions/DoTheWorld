
#include "code/doTheWorldSeparated.c"

int main(int argc, char *argv[]){
    //char *path2 = dtw_change_beginning_of_string("/home/teste",5,"/dev");
    //printf("%s\n",path2);
    //free(path2);
    struct DtwPath *path =dtw_constructor_path("/home/");
    path->represent(path);   
    return 0;
   
}
