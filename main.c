/*
#include "doTheWorld/doTheWorldmain.c"
void load_and_dump_string(){
    struct DtwTree *tree = dtw_tree_constructor();
    char *code = dtw_load_string_file_content("exemples.json");
    tree->loads_json_tree(tree, code);
    for (int i = 0; i < tree->size; i++){
        struct DtwTreePart *part = tree->tree_parts[i];
        struct DtwPath *path = part->path;
        path->add_start_dir(path,"exemples2");
        part->hardware_write(part);
      
    }
    
    tree->delete_tree(tree);
    free(code);
}

void load_hardware_and_dump_string(){
    struct DtwTree *tree = dtw_tree_constructor();
    tree->add_path_from_hardware(tree,"exemples",DTW_LOAD_CONTENT,DTW_PRESERVE_CONTENT);
    char *generated =tree->dumps_json_tree(
        tree,
        DTW_PRESERVE_CONTENT,
        DTW_PRESERVE_PATH_ATRIBUTES,
        DTW_PRESERVE_HARDWARE_DATA,
        DTW_PRESERVE_CONTENT_DATA,
        DTW_NOT_MINIFY
        );
    dtw_write_string_file_content("exemples.json",generated);
    free(generated);
    tree->delete_tree(tree);
}
*/
#include "doTheWorld/headers/imports.h"
#include "doTheWorld/headers/sha-256.h"
#include "doTheWorld/headers/string_array.h"
#include "doTheWorld/headers/string_functions.h"
#include "doTheWorld/headers/extras.h"


#include "doTheWorld/headers/io.h"
#include "doTheWorld/dependencies/sha-256.c"

#include "doTheWorld/headers/monodimension_listage_linux.h"
#include "doTheWorld/headers/monodimension_listage_win32.h"
#include "doTheWorld/headers/multidimension_listage.h"
#include "doTheWorld/headers/path.h"
#include "doTheWorld/headers/tree_part.h"



#include "doTheWorld/functions/monodimension_listage_linux.c"
#include "doTheWorld/functions/monodimension_listage_win32.c"
#include "doTheWorld/functions/multidimension_listage.c"
#include "doTheWorld/functions/io.c"
#include "doTheWorld/functions/string_functions.c"
#include "doTheWorld/functions/extras.c"
#include "doTheWorld/structs/string_array.c"
#include "doTheWorld/structs/path.c"
#include "doTheWorld/structs/tree_part/tree_part.c"
#include "doTheWorld/structs/tree_part/hardware_tree_part.c"
int main(int argc, char *argv[]){

  
    return 0;
}
