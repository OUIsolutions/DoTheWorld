#include "doTheWorldDevUsage.c"
int main(int argc, char *argv[]){
    
    struct DtwStringArray *dirs = dtw_list_dirs("exemple",true);
    dtw_represent_string_array(dirs);

}