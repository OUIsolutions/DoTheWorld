
#include "code/doTheWorldSeparated.h"

int main(int argc, char *argv[]){
    //char *path2 = dtw_change_beginning_of_string("/home/teste",5,"/dev");
    //printf("%s\n",path2);
    //free(path2);
    struct DtwStringArray *dirs = dtw_list_dirs_recursively("code",false);
    dirs->represent(dirs);
    dirs->delete_string_array(dirs);

    return 0;
}
