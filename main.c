
#include "code/doTheWorldSeparated.h"

int main(int argc, char *argv[]){
    const char *path ="exemples";
    struct DtwStringArray *array = dtw_list_dirs_recursively(path, true);

    array->represent(array);
    array->delete_string_array(array);
}
