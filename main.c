
#include "code/doTheWorldDevUsage.c"

int main(int argc, char *argv[]){
    
    struct DtwStringArray *files = dtw_list_files_recursively("/home");
    files->represent_string_array(files);
    return 0;
    
}
